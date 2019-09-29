#pragma once
#include "../include/Cpu.h"
#include "../include/Memory.h"
#include "../include/RegisterDebug.h"
#include "../include/TileViewer.h"
#include "../lib/imgui_club/imgui_memory_editor/imgui_memory_editor.h"
#include <imgui.h>
#include <string>
#include <type_traits>
#include <memory>

class Debugger
{
public:
  Debugger();
  int initGFX();

private:
  static int regValChange(ImGuiInputTextCallbackData *data);

  RegisterDebug regDebug;
  TileViewer tileViewer;
  Cpu cpu;
  Memory MMU;
  MemoryEditor memEditor;

  bool freeRun = false;
  bool breakPoint = false;
  char breakpointVal[5] = "0000";

  uint32_t t0;
};