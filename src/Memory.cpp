#include "../include/Memory.h"

uint8_t Memory::readByte(uint16_t address) const
{
    return memoryArray[address];
}

void Memory::writeByte(uint16_t address, uint8_t byte)
{
    memoryArray[address] = byte;
}
