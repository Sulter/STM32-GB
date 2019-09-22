cmake_minimum_required (VERSION 3.0)
project (GBA C CXX)

add_compile_options (-Wfatal-errors -Wall -Wextra -Werror -Og -g)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wpedantic")
find_package (GTest REQUIRED)
find_package (Threads REQUIRED)
find_package (SDL2 REQUIRED)
find_package (OpenGL REQUIRED)

include_directories (${GTEST_INCLUDE_DIRS})
include_directories (${SDL2_INCLUDE_DIRS})
include_directories (lib/glad/include)

set(imguiSrc
    lib/imgui/imgui.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/examples/imgui_impl_opengl3.cpp
    lib/imgui/examples/imgui_impl_sdl.cpp
)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library (imgui ${imguiSrc})
add_library (glad lib/glad/src/glad.c)

include_directories (lib/imgui)
include_directories (lib/examples)

add_executable (gba src/Cpu.cpp src/main.cpp src/Memory.cpp src/opcodes.cpp src/Lcd.cpp src/Debugger.cpp)
target_link_libraries (gba ${SDL2_LIBRARIES} ${OPENGL_gl_LIBRARY} imgui glad ${CMAKE_DL_LIBS})

add_executable (unitTest src/test/test.cpp src/test/opcodes-test.cpp src/test/Memory-test.cpp src/test/Cpu-test.cpp src/Cpu.cpp src/opcodes.cpp src/Memory.cpp src/Lcd.cpp)
target_link_libraries (unitTest gtest gtest_main pthread)