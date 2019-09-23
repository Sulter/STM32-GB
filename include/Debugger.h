#pragma once
#include "../include/Cpu.h"
#include "../include/Memory.h"
#include <imgui.h>
#include <string>
#include <type_traits>
#include "../lib/imgui_club/imgui_memory_editor/imgui_memory_editor.h"

template <typename T>
class DebugRegister
{
public:
  static_assert(std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value,
                "Only uint8_t and uint16_t registers allowed");

  virtual ~DebugRegister(){};

  static constexpr size_t editBufLenght = std::is_same<T, uint8_t>::value ? 3 : 5;
  char editBuf[editBufLenght];
  std::string name;
  T *reg = nullptr;

  char *getEditBuf()
  {
    sprintf(editBuf, "%04x", *reg);
    return editBuf;
  }

  void applyBuffer()
  {
    *reg = (int)strtol(editBuf, NULL, 16);
  }

  const char *getLabel()
  {
    std::string label = "##" + name;
    return label.c_str();
  };
};

class Debugger
{
public:
  Debugger();
  int initGFX();

private:
  int glyphWidth = 1;
  int hexWidth = 1;
  static int regValChange(ImGuiInputTextCallbackData *data);

  std::array<const std::string, 2> registerNames2B = {"PC", "SP"};
  std::array<const std::string, 10> registerNames1B = {"A", "B", "C", "D", "E", "H", "L", "flag"};
  std::array<DebugRegister<uint16_t>, 2> regs2B;
  std::array<DebugRegister<uint8_t>, 10> regs1B;

  Cpu cpu;
  Memory MMU;
  MemoryEditor memEditor;
};