#include <gtest/gtest.h>
#include <random>
#include "../../include/Memory.h"

// The fixture for testing class Foo.
class MemoryTest : public ::testing::Test
{
protected:
  MemoryTest() : rng(dev())
  {
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
  std::mt19937 rng;
  Memory mem;
};

TEST_F(MemoryTest, zeroInit)
{
  for (uint16_t i = 0; i < 0xffff; i++)
  {
    ASSERT_EQ(mem.readByte(i), 0);
  }
}

TEST_F(MemoryTest, writeReadByte)
{
  std::uniform_int_distribution<std::mt19937::result_type> byteDist(0, 0xff);
  std::uniform_int_distribution<std::mt19937::result_type> twoByteDist(0, 0xffff);

  for (size_t i = 0; i < 1000; i++)
  {
    uint8_t randByte = byteDist(rng);
    uint16_t address = twoByteDist(rng);
    mem.writeByte(address, randByte);
    ASSERT_EQ(randByte, mem.readByte(address));
  }
}

TEST_F(MemoryTest, clean)
{
  for (size_t i = 0; i < 0xffff; i++)
  {
    mem.writeByte(i, i);
  }

  mem.clean();

  for (size_t i = 0; i < 0xffff; i++)
  {
    ASSERT_EQ(0, mem.readByte(i));
  }
}
