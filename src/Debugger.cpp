#include "../include/Debugger.h"
#include <SDL.h>
#include <glad/glad.h>
#include "../lib/imgui/examples/imgui_impl_sdl.h"
#include "../lib/imgui/examples/imgui_impl_opengl3.h"

uint32_t global = 0xaaffaa;

Debugger::Debugger() : cpu(MMU)
{
  //setup memory - doesn't belong here!
  MMU.injectBoot();
  MMU.writeByte(0xff44, 0x90); //$0064, screen frame skip
  MMU.writeByte(0x0135, 0xe7); //ensure the checksum is correct

  //setup register stuff
  Cpu::registers &regRef = cpu.getRegisters();
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint16_t>>("pc", &regRef.pc));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint16_t>>("sp", &regRef.sp));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("A", &regRef.regA));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("B", &regRef.regB));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("C", &regRef.regC));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("D", &regRef.regD));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("E", &regRef.regE));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("H", &regRef.regH));
  regDebug.registers.push_back(std::make_unique<DebugRegister<uint8_t>>("L", &regRef.regL));

  regDebug.registers.push_back(std::make_unique<DebugRegisterFlag<uint8_t>>("Carry", &regRef.flagC));
  regDebug.registers.push_back(std::make_unique<DebugRegisterFlag<uint8_t>>("Half", &regRef.flagH));
  regDebug.registers.push_back(std::make_unique<DebugRegisterFlag<uint8_t>>("Zero", &regRef.flagZ));
  regDebug.registers.push_back(std::make_unique<DebugRegisterFlag<uint8_t>>("Sub", &regRef.flagN));
}

int Debugger::initGFX()
{
  // Setup SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
  {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 Core + GLSL 150
  const char *glsl_version = "#version 150";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window *window = SDL_CreateWindow("STM32-GB", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync

  // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
  bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
  bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
  bool err = gladLoadGL() == 0;
#else
  bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
  if (err)
  {
    fprintf(stderr, "Failed to initialize OpenGL loader!\n");
    return 1;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'misc/fonts/README.txt' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //io.Fonts->AddFontDefault();
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Main loop
  t0 = SDL_GetTicks();
  bool done = false;
  while (!done)
  {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
      ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }

    //Tile viewer window
    tileViewer.DrawWindow("Tile viewer", MMU.getMemory());

    //Gameboy drawing window

    //Registers window
    regDebug.DrawWindow("Registers");

    //Memory window
    memEditor.DrawWindow("Memory", MMU.getMemory(), Memory::memorySize);

    //Debugger window
    ImGui::Begin("Debugger");
    ImGui::BeginGroup();
    ImGui::Columns(2, nullptr, true);
    ImGui::Text("Address");
    ImGui::NextColumn();
    ImGui::Text("Value");
    ImGui::Separator();
    ImGui::NextColumn();

    ImGui::Text("%04x", cpu.getPC() - 1);
    ImGui::NextColumn();
    ImGui::Text("%02x", MMU.readByte(cpu.getPC() - 1));
    ImGui::NextColumn();
    char buf[5];
    sprintf(buf, "%04x", cpu.getPC());
    ImGui::Selectable(buf, true, ImGuiSelectableFlags_SpanAllColumns);
    ImGui::NextColumn();
    ImGui::Text("%02x", MMU.readByte(cpu.getPC()));
    ImGui::NextColumn();
    ImGui::Text("%04x", cpu.getPC() + 1);
    ImGui::NextColumn();
    ImGui::Text("%02x", MMU.readByte(cpu.getPC() + 1));
    ImGui::Columns(1);
    ImGui::Separator();
    ImGui::EndGroup();
    ImGui::NewLine();

    if (ImGui::IsKeyPressed(0x43)) //F10
    {
      cpu.execute();
    }

    if (ImGui::IsKeyPressed(0x3E)) //F5
    {
      freeRun = true;
      //always take one step, to get out of breakpoint
      cpu.execute();
    }

    if (ImGui::IsKeyPressed(0x42)) //F9
    {
      freeRun = false;
    }

    ImGui::Columns(3, nullptr, false);
    if (ImGui::Button("Step (F10)"))
    {
      cpu.execute();
    }

    ImGui::NextColumn();
    if (ImGui::Button("Freerun (F5)"))
    {
      freeRun = true;
      //always take one step, to get out of breakpoint
      cpu.execute();
    }
    ImGui::NextColumn();
    if (ImGui::Button("Stop (F9)"))
    {
      freeRun = false;
    }

    ImGui::Columns(2, nullptr, false);
    ImGui::Checkbox("Breakpoint", &breakPoint);
    ImGui::NextColumn();
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_NoHorizontalScroll | ImGuiInputTextFlags_AlwaysInsertMode;
    if (ImGui::InputText("##breakpoint", breakpointVal, 5, flags))
    {
      breakPoint = true;
    }
    ImGui::End();

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);

    //process as much as necessary
    uint32_t msPassed = SDL_GetTicks() - t0;
    t0 = SDL_GetTicks();
    if (freeRun)
    {
      for (uint32_t i = 0; i < msPassed * 1049; i += cpu.getLastCycle())
      {
        cpu.execute();
        if (breakPoint)
        {
          if (cpu.getPC() == (uint32_t)strtol(breakpointVal, NULL, 16))
          {
            freeRun = false;
            break;
          }
        }
      }
    }
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}