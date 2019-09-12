#include <gtest/gtest.h>
#include "../../include/Cpu.h"

// The fixture for testing class Foo.
class CpuTest : public Cpu, public ::testing::Test
{
protected:
  CpuTest()
  {
  }

  ~CpuTest() override
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }
};

TEST_F(CpuTest, pcNop)
{
  runOpcode(0x01);
  EXPECT_EQ(getPC(), 3);
}