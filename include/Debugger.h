#pragma once
#include "../include/Cpu.h"
#include "../include/Memory.h"


class Debugger
{
  public:
  Debugger();
  int initGFX();
  private:

  Cpu cpu;
  Memory MMU;
};