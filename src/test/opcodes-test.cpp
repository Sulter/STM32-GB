#include <gtest/gtest.h>
#include "../../include/Cpu.h"

// The fixture for testing class Foo.
class OpcodeTest : public Cpu, public ::testing::Test
{
protected:
  OpcodeTest()
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