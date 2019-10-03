#include <gtest/gtest.h>
#include <vector>
#include "../../include/Disassembler.h"

class DisassemblerTest : public ::testing::Test
{
public:
  DisassemblerTest()
  {
  }

  ~DisassemblerTest() override
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }

  Disassembler mnemonic;
};

class DisassemblerTestOpcodes : public DisassemblerTest,
                            public testing::WithParamInterface<Code>
{
};

Code arrCode[] = {
    0x0, "NOP", 1, 4, "----",
    0x1, "LD BC,d16", 3, 12, "----",
    0x2, "LD (BC),A", 1, 8, "----",
    0xff, "RST 38H", 1, 16, "----",
    0x00 + 0xff + 1, "RLC B", 2, 8, "Z00C",
    0xff + 0xff + 1, "SET 7,A", 2, 8, "----"};

INSTANTIATE_TEST_CASE_P(Group, DisassemblerTestOpcodes,
                        testing::ValuesIn(arrCode));

TEST_P(DisassemblerTestOpcodes, opcodesToDisassemblers)
{
  EXPECT_EQ(mnemonic(GetParam().opcode).mnemonic, GetParam().mnemonic);
  EXPECT_EQ(mnemonic(GetParam().opcode).flags, GetParam().flags);
  EXPECT_EQ(mnemonic(GetParam().opcode).lenght, GetParam().lenght);
  EXPECT_EQ(mnemonic(GetParam().opcode).cycles, GetParam().cycles);
}

TEST_P(DisassemblerTestOpcodes, mnemonicsToOpcode)
{
  EXPECT_EQ(mnemonic(GetParam().mnemonic).mnemonic, GetParam().mnemonic);
  EXPECT_EQ(mnemonic(GetParam().mnemonic).flags, GetParam().flags);
  EXPECT_EQ(mnemonic(GetParam().mnemonic).lenght, GetParam().lenght);
  EXPECT_EQ(mnemonic(GetParam().mnemonic).cycles, GetParam().cycles);
}

TEST_F(DisassemblerTest, mnemonicsToOpcodeSimilar)
{
  std::string str = "LD bc d16 ";
  Code code = {0x1, "LD BC,d16", 3, 12, "----"};
  EXPECT_EQ(mnemonic(str).mnemonic, code.mnemonic);
  EXPECT_EQ(mnemonic(str).flags, code.flags);
  EXPECT_EQ(mnemonic(str).lenght, code.lenght);
  EXPECT_EQ(mnemonic(str).cycles, code.cycles);
}

TEST_F(DisassemblerTest, dissasambleSimple)
{
  Code codeDissasmable = mnemonic.disassemble(0x0000, {mnemonic("nop").opcode, mnemonic("nop").opcode, mnemonic("nop").opcode});
  Code code = {0x0, "NOP", 1, 4, "----"};
  EXPECT_EQ(code.mnemonic, codeDissasmable.mnemonic);
  EXPECT_EQ(code.flags, codeDissasmable.flags);
  EXPECT_EQ(code.lenght, codeDissasmable.lenght);
  EXPECT_EQ(code.cycles, codeDissasmable.cycles);

  codeDissasmable = mnemonic.disassemble(0x0001, {mnemonic("nop").opcode, mnemonic("nop").opcode, mnemonic("nop").opcode});
  EXPECT_EQ(code.mnemonic, codeDissasmable.mnemonic);
  EXPECT_EQ(code.flags, codeDissasmable.flags);
  EXPECT_EQ(code.lenght, codeDissasmable.lenght);
  EXPECT_EQ(code.cycles, codeDissasmable.cycles);
}

TEST_F(DisassemblerTest, dissasambleDatad16)
{
  Code codeDissasmable = mnemonic.disassemble(0x0000, {mnemonic("LD BC,d16").opcode, 0x11, 0x22});
  EXPECT_EQ("LD BC,$2211", codeDissasmable.mnemonic);

  codeDissasmable = mnemonic.disassemble(0x0001, {0x11, 0x22, 0x33});
  EXPECT_EQ("DATA", codeDissasmable.mnemonic);

  codeDissasmable = mnemonic.disassemble(0x0002, {0x11, 0x22, 0x33});
  EXPECT_EQ("DATA", codeDissasmable.mnemonic);
}

TEST_F(DisassemblerTest, dissasambleDatad8)
{
  Code codeDissasmable = mnemonic.disassemble(0x0000, {mnemonic("JR C,r8").opcode, 0x01, 0x22});
  EXPECT_EQ("JR C,+1", codeDissasmable.mnemonic);

  codeDissasmable = mnemonic.disassemble(0x0001, {0x11, 0x22, 0x33});
  EXPECT_EQ("DATA", codeDissasmable.mnemonic);
}

TEST_F(DisassemblerTest, dissasambleCB)
{
  Code codeDissasmable = mnemonic.disassemble(0x0000, {0xcb, 0x11, 0x22});
  EXPECT_EQ("PREFIX CB", codeDissasmable.mnemonic);

  codeDissasmable = mnemonic.disassemble(0x0001, {0x11, 0x22, 0x33});
  EXPECT_EQ("RL C", codeDissasmable.mnemonic);
}