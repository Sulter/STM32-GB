#include <gtest/gtest.h>
#include "../../include/Cpu.h"
#include "../../include/Memory.h"
#include "../../include/Disassembler.h"

// The fixture for testing class Foo.
class OpcodeTest : public Cpu, public ::testing::Test
{
protected:
  OpcodeTest() : Cpu(Cpu(MMU))
  {
  }

  ~OpcodeTest() override
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }

  Memory MMU;
  Disassembler disassembler;
};

TEST_F(OpcodeTest, ldSPnnByte)
{
  getMMU().writeByte(1, 0xab);
  getMMU().writeByte(2, 0xcd);
  runOpcode(0x31);
  EXPECT_EQ(getPC(), 3);
  EXPECT_EQ(getTotalCycles(), 12);
  EXPECT_EQ(getRegisters().sp, 0xcdab);
}

TEST_F(OpcodeTest, rlC)
{
  getRegisters().regC = 0xaa;
  runOpcode(disassembler("PREFIX CB").opcode);
  runOpcode(disassembler("RL C").opcode);
  EXPECT_EQ(getRegisters().regC, 0x54);
  EXPECT_TRUE(getRegisters().flagC);
  runOpcode(disassembler("PREFIX CB").opcode);
  runOpcode(disassembler("RL C").opcode);
  EXPECT_EQ(getRegisters().regC, 0xa9);
  EXPECT_FALSE(getRegisters().flagC);
}

TEST_F(OpcodeTest, rlA)
{
  getRegisters().regA = 0xaa;
  runOpcode(0x17);
  EXPECT_EQ(getRegisters().regA, 0x54);
  EXPECT_TRUE(getRegisters().flagC);
  runOpcode(0x17);

  EXPECT_EQ(getRegisters().regA, 0xa9);
  EXPECT_FALSE(getRegisters().flagC);
}

TEST_F(OpcodeTest, swapA)
{
  getRegisters().regA = 0xdb;
  runOpcode(disassembler("PREFIX CB").opcode);
  runOpcode(disassembler("SWAP A").opcode);
  EXPECT_EQ(getRegisters().regA, 0xbd);
  EXPECT_FALSE(getRegisters().flagZ);
}

TEST_F(OpcodeTest, pushNpop)
{
  getMMU().writeByte(1, 0xff);
  getMMU().writeByte(2, 0x00);
  runOpcode(static_cast<uint16_t>(instructions::ldSPnn));

  getMMU().writeByte(getRegisters().pc + 1, 0xab);
  getMMU().writeByte(getRegisters().pc + 2, 0xcd);

  runOpcode(static_cast<uint16_t>(instructions::ldBCnn));

  EXPECT_EQ(getRegisters().regB, 0xcd);
  EXPECT_EQ(getRegisters().regC, 0xab);

  runOpcode(static_cast<uint16_t>(instructions::pushBC));

  getRegisters().regB = 0x00;
  getRegisters().regC = 0xff;

  EXPECT_EQ(getRegisters().sp, 0x00ff - 2);
  EXPECT_EQ(getMMU().readByte(getRegisters().sp), 0xcd);
  EXPECT_EQ(getMMU().readByte(getRegisters().sp + 1), 0xab);

  runOpcode(static_cast<uint16_t>(instructions::popBC));
  EXPECT_EQ(getRegisters().sp, 0x00ff);

  EXPECT_EQ(getRegisters().regB, 0xcd);
  EXPECT_EQ(getRegisters().regC, 0xab);
}

TEST_F(OpcodeTest, rst)
{
  getRegisters().pc = 0;
  runOpcode(disassembler("RST 38H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x38);
  runOpcode(disassembler("RST 28H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x28);
  runOpcode(disassembler("RST 18H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x18);
  runOpcode(disassembler("RST 08H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x08);
  runOpcode(disassembler("RST 00H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x00);
  runOpcode(disassembler("RST 10H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x10);
  runOpcode(disassembler("RST 20H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x20);
  runOpcode(disassembler("RST 30H").opcode);
  EXPECT_EQ(getRegisters().pc, 0x30);
}