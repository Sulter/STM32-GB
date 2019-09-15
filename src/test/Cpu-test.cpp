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

TEST_F(CpuTest, integrationBlop)
{
  //run bootstrap rom to see if we crash?
  getMMU().injectBoot();
  for (long long unsigned int i = 0; i < 1000000; i++)
    execute();

  // std::cout << getInfo() << std::endl
  //           << "Cyles: " << getTotalCycles();
}