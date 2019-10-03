#include "../include/Disassembler.h"

std::ostream &operator<<(std::ostream &out, const Disassembler &b)
{
  for (auto const &[key, val] : b.disassembler)
  {
    if (val.mnemonic != "inv" && val.mnemonic != "DATA" && val.mnemonic != "PREFIX CB")
    {
      static const int desiredWidth = 15;
      int spaceNr = desiredWidth - val.mnemonic.length();
      std::string spaces;
      spaces.append(spaceNr, ' ');
      out << val.mnemonic
          << spaces
          << "; $"
          << std::hex
          << key
          << std::endl;
    }
  }
  return out;
}

Code Disassembler::operator()(uint16_t opcode)
{
  for (auto i : mnemonics)
  {
    if (i.opcode == opcode)
      return i;
  }
  return invalid;
}

Code Disassembler::operator()(std::string mnemonic)
{
  for (auto i : mnemonics)
  {
    if (simplifyMnemonic(i.mnemonic) == simplifyMnemonic(mnemonic))
      return i;
  }
  return invalid;
}

std::string Disassembler::simplifyMnemonic(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  std::replace(str.begin(), str.end(), '(', ' ');
  std::replace(str.begin(), str.end(), ')', ' ');
  std::replace(str.begin(), str.end(), ',', ' ');
  str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
  return str;
}

bool Disassembler::findAndReplace(std::string &str, std::string find, std::string replacement)
{
  size_t index = str.find(find);
  if (index != std::string::npos)
  {
    str.replace(index, find.length(), replacement);
    return true;
  }
  else
  {
    return false;
  }
}

Code Disassembler::handleLongInstruction(Code code, uint16_t pc, std::array<uint16_t, 3> opcodes)
{
  if (code.lenght == 2)
  {
    static const size_t strLenght = 5;
    char str[strLenght];
    sprintf(str, "$%02x", opcodes[1]);

    if (findAndReplace(code.mnemonic, "d8", str) || findAndReplace(code.mnemonic, "a8", str))
    {
      disassembler[pc + 1] = data;
    }

    sprintf(str, "%+d", static_cast<int8_t>(opcodes[1]));
    if (findAndReplace(code.mnemonic, "r8", str))
    {
      disassembler[pc + 1] = data;
    }

    disassembler[pc] = code;
    return code;
  }
  else
  {
    disassembler[pc + 1] = data;
    disassembler[pc + 2] = data;

    static const size_t strLenght = 6;
    char str[strLenght];
    sprintf(str, "$%02x%02x", opcodes[2], opcodes[1]);

    findAndReplace(code.mnemonic, "d16", str);
    findAndReplace(code.mnemonic, "a16", str);

    disassembler[pc] = code;
    return code;
  }
}

Code Disassembler::disassemble(uint16_t pc, std::array<uint16_t, 3> opcodes)
{
  //see if already dissambled
  auto search = disassembler.find(pc);
  if (search != disassembler.end())
  {
    return search->second;
  }
  else
  {
    Code code = (*this)(opcodes[0]);
    if (code.lenght > 1) //handle instructions with data
    {
      return handleLongInstruction(code, pc, opcodes);
    }
    else if (code.opcode == 0xcb) //handle cb instructions
    {
      disassembler[pc] = code;
      disassembler[pc + 1] = (*this)(opcodes[1] + 0xff + 1);
      return code;
    }
    else //handle normal 1-byte instructions
    {
      disassembler[pc] = code;
      return code;
    }
  }
}