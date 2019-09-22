#include <gtest/gtest.h>
#include "../../include/Cpu.h"
#include "../../include/Memory.h"

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

  EXPECT_EQ(getRegisters().sp, 0x00ff - 2);
  EXPECT_EQ(getMMU().readByte(getRegisters().sp),  0xcd);
  EXPECT_EQ(getMMU().readByte(getRegisters().sp + 1),  0xab);

  runOpcode(static_cast<uint16_t>(instructions::popBC));
  EXPECT_EQ(getRegisters().sp, 0x00ff);

  EXPECT_EQ(getRegisters().regB, 0xcd);
  EXPECT_EQ(getRegisters().regC, 0xab);

}