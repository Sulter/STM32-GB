#pragma once
#include <imgui.h>
#include <string>
#include <bitset>
#include <cmath>

class DisplayViewer
{
public:
  void DrawWindow(std::string name, uint8_t *memPtr)
  {
    ImGui::Begin(name.c_str(), nullptr, ImVec2(pixelSize * resX + xOffset, pixelSize * resY + yOffset), 1.0f, ImGuiWindowFlags_NoResize);
    //ImGui::SliderInt("size", &pixelSize, 1, 30);

    if (!hasResized)
      ImGui::SetWindowSize(ImVec2(pixelSize * resX + xOffset, pixelSize * resY + yOffset));

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();

    //draw BG
    draw_list->AddRectFilled(p, ImVec2(p.x + pixelSize * resX, p.y + pixelSize * resY), colOff);

    const uint16_t startAddrTileMap = 0x9800;
    const uint16_t startAddrTiles = 0x8000;

    for (uint16_t tileY = 0; tileY < 32; tileY++)
    {
      for (uint16_t tileX = 0; tileX < 32; tileX++)
      {
        for (uint16_t line = 0; line < 8; line++)
        {
          volatile uint16_t tileIdAddr = startAddrTileMap + tileX + tileY * 32;
          uint8_t tileId = memPtr[tileIdAddr];
          uint16_t tileAddr = startAddrTiles + tileId * 16; 
          std::bitset<8> tileLine1 = memPtr[tileAddr + 2 * line];
          std::bitset<8> tileLine2 = memPtr[tileAddr + 2 * line + 1];
          tileLine1 |= tileLine2;
          for (size_t i = 0; i < tileLine1.size(); i++)
          {
            ImVec2 xy = ImVec2(p.x + pixelSize * 8 - pixelSize * i, p.y + pixelSize * line);
            xy = ImVec2(xy.x + pixelSize * tileX * tileSize, xy.y + pixelSize * tileY * tileSize - memPtr[0xff42] * pixelSize);
            if (tileLine1[i])
              draw_list->AddRectFilled(xy, ImVec2(xy.x + pixelSize, xy.y + pixelSize), colOn);
          }
        }
      }
    }

    ImGui::End();
  };

private:
  int pixelSize = 2;
  bool hasResized = false;

  ImVec4 colfOff = ImVec4(0.5f, 0.6f, 0.4f, 1.0f);
  ImU32 colOff = ImColor(colfOff);
  ImVec4 colfOn = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  ImU32 colOn = ImColor(colfOn);

  static constexpr int xOffset = 150;
  static constexpr int yOffset = 100;
  static constexpr int tileSize = 8;
  static constexpr int resX = 256;
  static constexpr int resY = 256;
};