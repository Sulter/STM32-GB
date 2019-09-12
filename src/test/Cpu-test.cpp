#include <gtest/gtest.h>
#include "../../include/Cpu.h"

// The fixture for testing class Foo.
class CpuTest : public ::testing::Test
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

  Cpu cpu;
};

TEST_F(CpuTest, instruction1test)
{
}