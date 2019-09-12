#include "../include/Memory.h"

Memory::Memory()
{
  memoryArray.fill(0);
}

void Memory::clean()
{
  memoryArray.fill(0);
}

uint8_t Memory::readByte(uint16_t address) const
{
  return memoryArray[address];
}

void Memory::writeByte(uint16_t address, uint8_t byte)
{
  memoryArray[address] = byte;
}
