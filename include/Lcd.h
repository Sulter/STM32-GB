#pragma once
#include <cstdint>
#include <array>
#include <bitset>
#include "../include/Memory.h"

class Lcd
{
public:
  using drawCallback = void (*)(uint8_t, uint8_t);
  Lcd(Memory &m) : MMU(m){};
  void updateLcd();

private:

  struct registers
  {
    uint8_t SCROLLX;
    uint8_t SCROLLY;
    std::bitset<8> LCDC;

    enum class regAddr : uint16_t
    {
      SCROLLX = 0xff43,
      SCROLLY = 0xff42,
      LCDC = 0xff40
    };

    enum class LCDC
    {
      BGnWindow,
      sprite,
      spriteSize,
      mapSelect,
      BGnWindowSelect,
      windowOn,
      windowTileSelect,
      lcdOn
    };

    void setRegisters(Memory &MMU)
    {
      LCDC = MMU.readByte(static_cast<uint16_t>(regAddr::LCDC));
      SCROLLY = MMU.readByte(static_cast<uint16_t>(regAddr::SCROLLY));
      SCROLLX = MMU.readByte(static_cast<uint16_t>(regAddr::SCROLLX));
    }
  };

  registers regs;

  drawCallback drawPixel;
  static constexpr unsigned int resx = 160;
  static constexpr unsigned int resy = 144;

  Memory &MMU;
};