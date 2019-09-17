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

TEST_F(CpuTest, DMGboot)
{
  //run bootstrap rom to see if we crash
  getMMU().injectBoot();
  getMMU().writeByte(0xff44, 0x90); //$0064, screen frame skip
  getMMU().writeByte(0x0135, 0xe7); //ensure the checksum is correct
  
  long long unsigned int i = 0;
  while(getRegisters().pc != 0x100)
  {
    execute();
    ASSERT_LT(i++, 15000000); //shouldn't take more?
    
  }
    
}