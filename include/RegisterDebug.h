#pragma once
#include <string>
#include <type_traits>
#include <memory>
#include <imgui.h>
#include <iostream>

class DebugReg
{
public:
  DebugReg(std::string name) : name(name), label("##" + name){};

  virtual char *getEditBuf() = 0;
  virtual void applyBuffer() = 0;
  virtual size_t getBufLenght() = 0;

  std::string getName()
  {
    return name;
  }

  const char *getLabel()
  {
    return label.c_str();
  };

private:
  std::string name;
  std::string label;
};

template <size_t N>
class DebugRegisterFlag : public DebugReg
{
  public:
  private:
};

template <typename T>
class DebugRegister : public DebugReg
{
public:
  DebugRegister(std::string name, T *val) : DebugReg(name), reg(val){};
  static_assert(std::is_same<T, uint8_t>::value || std::is_same<T, uint16_t>::value || std::is_same<T, uint32_t>::value,
                "Only uint8_t, uint16_t and uint32_t registers allowed");

  size_t getBufLenght()
  {
    return editBufLenght;
  }

  char *getEditBuf()
  {
    if (editBufLenght == 3)
    {
      sprintf(editBuf, "%02x", *reg);
    }
    else if (editBufLenght == 5)
    {
      sprintf(editBuf, "%04x", *reg);
    }
    else
    {
      sprintf(editBuf, "%08x", *reg);
    }
    return editBuf;
  }

  void applyBuffer()
  {
    *reg = (unsigned int)strtol(editBuf, NULL, 16);
  }

private:
  static constexpr size_t editBufLenght = std::is_same<T, uint8_t>::value ? 3 : (std::is_same<T, uint16_t>::value ? 5 : 9);
  char editBuf[editBufLenght];
  T *reg = nullptr;
};

class RegisterDebug
{
public:
  static int regValChange(ImGuiInputTextCallbackData *)
  {
    std::cout << "change!" << std::endl;
    return 1;
  }

  void DrawWindow(std::string name)
  {
    //setup character widths
    float glyphWidth = ImGui::CalcTextSize("F").x + 1;
    float hexWidth = (float)(int)(glyphWidth);
    ImGui::Begin(name.c_str());

    ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_NoHorizontalScroll | ImGuiInputTextFlags_AlwaysInsertMode;
    ImGui::Columns(2, nullptr, true);

    for (auto &reg : registers)
    {
      ImGui::Text("%s", reg->getName().c_str());
      ImGui::NextColumn();
      ImGui::PushItemWidth(hexWidth * static_cast<float>(reg->getBufLenght()) - 1.0f);
      if (ImGui::InputText(reg->getLabel(), reg->getEditBuf(), reg->getBufLenght(), flags, regValChange))
      {
        reg->applyBuffer();
      }
      ImGui::PopItemWidth();
      ImGui::Separator();
      ImGui::NextColumn();
    }
    ImGui::End();
  };
  std::vector<std::unique_ptr<DebugReg>> registers;
};