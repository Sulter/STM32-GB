#pragma once
#include <imgui.h>
#include <string>
#include <bitset>
#include <cmath>

class TileViewer
{
public:
  void DrawWindow(std::string name, uint8_t *memPtr)
  {
    ImGui::Begin(name.c_str(), nullptr, ImVec2(pixelSize * tileSize + xOffset, pixelSize * tileSize + yOffset), 1.0f, ImGuiWindowFlags_NoResize);
    ImGui::SliderInt("size", &pixelSize, 1, 30);
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_NoHorizontalScroll | ImGuiInputTextFlags_AlwaysInsertMode;
    if (ImGui::InputText("addr", inputBuf, 5, flags))
    {
      tileAddr = (uint32_t)strtol(inputBuf, NULL, 16);
    }

    if (!hasResized)
      ImGui::SetWindowSize(ImVec2(pixelSize * tileSize + xOffset, pixelSize * tileSize + yOffset));

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();

    for (uint16_t line = 0; line < 8; line++)
    {
      std::bitset<8> tileLine1 = memPtr[tileAddr + 2 * line];
      std::bitset<8> tileLine2 = memPtr[tileAddr + 2 * line + 1];
      tileLine1 |= tileLine2;
      for (size_t i = 0; i < tileLine1.size(); i++)
      {
        ImVec2 xy = ImVec2(p.x + pixelSize * 8 - pixelSize * i, p.y + pixelSize * line);
        if (tileLine1[i])
          draw_list->AddRectFilled(xy, ImVec2(xy.x + pixelSize, xy.y + pixelSize), colOn);
        else
          draw_list->AddRectFilled(xy, ImVec2(xy.x + pixelSize, xy.y + pixelSize), colOff);
      }
    }

    if (ImGui::IsMousePosValid())
    {
      ImGuiIO &io = ImGui::GetIO();

      if (ImGui::IsMouseClicked(0))
      {
        float x = io.MousePos.x;
        float y = io.MousePos.y;
        x = x - p.x - pixelSize;
        y = y - p.y;

        //check if mouse inside drawing area
        if (x >= 0 && x <= pixelSize * 8 && y >= 0 && y <= pixelSize * 8)
        {
          int tilePxX = static_cast<int>(round(x)) / (pixelSize);
          int tilePxY = static_cast<int>(round(y)) / (pixelSize);

          changeTilePixel(tilePxX, tilePxY, memPtr);
        }
      }
    }

    ImGui::End();
  };

private:
  void changeTilePixel(int tilePxX, int tilePxY, uint8_t *memPtr)
  {
    if (tilePxY < 0 && tilePxY > 7 && tilePxX < 0 && tilePxX > 7)
      return;

    //because of lsb
    tilePxX = 7 - tilePxX;

    if ((memPtr[tileAddr + 2 * tilePxY] & (1 << tilePxX)) | (memPtr[tileAddr + 2 * tilePxY + 1] & (1 << tilePxX)))
    {
      memPtr[tileAddr + 2 * tilePxY] &= ~(1 << tilePxX);
      memPtr[tileAddr + 2 * tilePxY + 1] &= ~(1 << tilePxX);
    }
    else
    {
      memPtr[tileAddr + 2 * tilePxY] |= 1 << tilePxX;
      memPtr[tileAddr + 2 * tilePxY + 1] |= 1 << tilePxX;
    }
  }

  int pixelSize = 5;
  bool hasResized = false;

  ImVec4 colfOff = ImVec4(0.5f, 0.6f, 0.4f, 1.0f);
  ImU32 colOff = ImColor(colfOff);
  ImVec4 colfOn = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  ImU32 colOn = ImColor(colfOn);

  uint16_t tileAddr = 0x8205; //R logo
  char inputBuf[5] = "8205";

  static constexpr int xOffset = 150;
  static constexpr int yOffset = 100;
  static constexpr int tileSize = 8;
};