#include "../include/Cpu.h"
#include <iostream>

Cpu::Cpu():
    opcodeMap{&Cpu::DCC, &Cpu::DCC}
{
    //set stack pointer, program counter, and the registers to 0
    pc = 0;
    sp = 0;
    regA = 0;
    regB = 0;
    regC = 0;
    regD = 0;
    regE = 0;
    regH = 0;
    regL = 0;
    regF = 0;

    (this->*opcodeMap[0])();


}


void Cpu::DCC()
{
    std::cout<<44;
}
