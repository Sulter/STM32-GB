#include "../include/Cpu.h"
#include <cstdio>

void Cpu::nop()
{
    lastCycle=4;
    pc++;
    printf("\nNop");
}

void Cpu::incB()
{
    regB++;//increase the register

    setFlag(2, 0, 2, -1, regB, 1); //"Z 0 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc
}

void Cpu::decB()
{
    regB--;//decrease the register

    setFlag(2, 1, 3, -1, regB, 1); //"Z 1 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc
}

void Cpu::rlcA()
{
    unsigned char temp = regA & (0x80);
    regA<<=1;
    regA|=temp>>7;
    setFlag(0,0,0,3,temp, 0xff);

    lastCycle = 4;
    pc++;

    printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n",regA, pc, flagZ, flagN, flagH, flagC);
}

void Cpu::incC()
{
    regC++;//increase the register

    setFlag(2, 0, 2, -1, regC, 1); //"Z 0 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc
}

void Cpu::decC()
{
    regC--;//decrease the register

    setFlag(2, 1, 3, -1, regC, 1); //"Z 1 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc
}

void Cpu::rrcA()
{
    printf("\nbefore operation regA: %d", regA);
    unsigned char temp = regA & (0x01);
    regA>>=1;
    regA|=temp<<7;
    printf("\ntemp is: %d", temp);
    setFlag(0,0,0,3,0xff,temp);

    lastCycle = 4;
    pc++;

    printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n",regA, pc, flagZ, flagN, flagH, flagC);
}

void Cpu::incD()
{
    regD++;//increase the register

    setFlag(2, 0, 2, -1, regD, 1); //"Z 0 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc
}

void Cpu::decD()
{
    regD--;//decrease the register

    setFlag(2, 1, 3, -1, regD, 1); //"Z 1 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc
}

void Cpu::rlA()
{
    unsigned char temp = regA & (0x80);
    regA<<=1;
    regA|=flagC;
    setFlag(0,0,0,3,temp, 0xff);

    lastCycle = 4;
    pc++;

    printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n",regA, pc, flagZ, flagN, flagH, flagC);

}

void Cpu::incA()
{
    regA++;//increase the register

    setFlag(2, 0, 2, -1, regA, 1); //"Z 0 H -"

    lastCycle=4;//add number of cycles
    pc++;//increase the program pc

    printf("\nregA: %d\npc: %d\nZ: %d N: %d H: %d C: %d\n",regA, pc, flagZ, flagN, flagH, flagC);
}
