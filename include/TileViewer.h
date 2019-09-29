#pragma once
#include <imgui.h>
#include <string>
#include <bitset>

class TileViewer
{
public:
  void DrawWindow(std::string name, uint8_t *memPtr)
  {
    ImGui::Begin(name.c_str(), nullptr, ImVec2(pixelSize * 8 + 150, pixelSize * 8 + 100), 1.0f, ImGuiWindowFlags_NoResize);
    ImGui::SliderInt("size", &pixelSize, 1, 30);
    ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_NoHorizontalScroll | ImGuiInputTextFlags_AlwaysInsertMode;
    if (ImGui::InputText("addr", inputBuf, 5, flags))
    {
      tileAddr = (uint32_t)strtol(inputBuf, NULL, 16);
    }

    if (!hasResized)
      ImGui::SetWindowSize(ImVec2(pixelSize * 8 + 150, pixelSize * 8 + 100));
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();

    for (uint16_t line = 0; line < 8; line++)
    {
      //volatile uint16_t tileIdAddr = startAddrTiles; //startAddr + tileY + tileX;
      //volatile uint8_t tileId = MMU.readByte(tileIdAddr);
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

    ImGui::End();
  };

private:
  int pixelSize = 5;
  bool hasResized = false;

  ImVec4 colfOff = ImVec4(0.5f, 0.6f, 0.4f, 1.0f);
  ImU32 colOff = ImColor(colfOff);
  ImVec4 colfOn = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
  ImU32 colOn = ImColor(colfOn);

  uint16_t tileAddr = 0x8205; //R logo
  char inputBuf[5] = "8205";
};