#include "../include/Cpu.h"
#include "../include/Memory.h"
#include <iostream>
#include <cstdint>
#include <cstdio>

int main()
{
    Memory myMMU;
    Cpu myCpu(myMMU);
    myCpu.incA();
    return 0;
}
