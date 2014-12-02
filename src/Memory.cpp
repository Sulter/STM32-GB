#include "../include/Memory.h"

uint8_t Memory::readByte(uint16_t address) const
{
    return memoryArray[address];
}

void Memory::writeByte(uint16_t address, uint8_t byte)
{
    memoryArray[address] = byte;
}

uint16_t Memory::readWord(uint16_t address) const
{
    uint16_t temp = memoryArray[address];
    temp |= (memoryArray[address+1] << 7);
    return temp;
}

void Memory::writeWord(uint16_t address, uint16_t word)
{
    memoryArray[address] = (word & 0xff);
    memoryArray[address+1] = (word & 0xff00);
}
