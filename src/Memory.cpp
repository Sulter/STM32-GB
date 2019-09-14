#include "../include/Memory.h"

Memory::Memory()
{
  memoryArray.fill(0);
}

void Memory::P1Call(uint16_t)
{
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

  auto it = std::find(IOregs.begin(), IOregs.end(), address);
  if(it != IOregs.end())
    (this->*it->Memory::IOreg::callback)(address);
}
