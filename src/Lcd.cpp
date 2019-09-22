#include "../include/Lcd.h"
#include <iostream>

void Lcd::updateLcd()
{
  regs.setRegisters(MMU);

  uint16_t startAddr = 0x9800;
  uint16_t startAddr2 = 0x8000;

  // for(uint16_t i = startAddr2; i < 0x8fff; i++)
  // {
  //   uint8_t tileLine1 = MMU.readByte(i);

  //   std::cout << std::hex << "0x" << int(tileLine1) << " ";
  // }

  for (uint16_t tileY = 0; tileY < 32; tileY++)
  {
    for (uint16_t i = 0; i < 8; i++)
    {
      for (uint16_t tileX = 0; tileX < 32; tileX++)
      {

        volatile uint16_t tileIdAddr = startAddr + tileY + tileX;
        volatile uint8_t tileId = MMU.readByte(tileIdAddr);
        std::bitset<8> tileLine1 = MMU.readByte(startAddr2 + tileId * 16 + 2 * i);
        std::bitset<8> tileLine2 = MMU.readByte(startAddr2 + tileId * 16 + 2 * i + 1);
        tileLine1 |= tileLine2;
        std::cout << tileLine1;
      }
      std::cout << std::endl;
    }
  }



  // uint8_t xTilePos = 0;
  // uint8_t yTilePos = 0;
  // for (uint16_t i = 0x9800; i < 0x9bff; i++)
  // {
  //   for (uint16_t yInTile = 0; yInTile < 8; yInTile++)
  //   {
  //     uint16_t tileId = MMU.readByte(i + yInTile);

  //     std::bitset<8> tile = uint16_t(MMU.readByte((tileId * 16) + 2 * (yTilePos % 8)));

  //     std::cout << tile;
  //   }

  //   std::cout<<std::endl;

  //   xTilePos++;
  //   if (xTilePos == 32)
  //   {
  //     xTilePos = 0;
  //     yTilePos++;
  //   }
  // }
}