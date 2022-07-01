#include <gtest/gtest.h>
#include "solution.cpp"

TEST(example, one)
{
  auto sut = cycle({0, 1, 1, 2, 1}, 80);
  EXPECT_EQ(5934, value(sut));
}
