#include <gtest/gtest.h>
#include <random>
#include "../../include/Memory.h"

// The fixture for testing class Foo.
class MemoryTest : public ::testing::Test
{
protected:
  MemoryTest()
  {
    std::mt19937 rng(dev());
  }

  ~MemoryTest() override
  {
  }

  void SetUp() override
  {
  }

  void TearDown() override
  {
  }

  std::random_device dev;
  Memory mem;
};

TEST_F(MemoryTest, zeroInit)
{
  for (uint16_t i = 0; i < 0xffff; i++)
  {
    ASSERT_EQ(mem.readByte(i), 0);
  }
}

TEST_F(MemoryTest, writeByte)
{
}

TEST_F(MemoryTest, readByteSequence)
{
}