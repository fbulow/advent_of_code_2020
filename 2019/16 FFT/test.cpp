#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(keep_one_digit, all)
{
  EXPECT_EQ(0, keep_one_digit(0));
  EXPECT_EQ(0, keep_one_digit(10));
  EXPECT_EQ(0, keep_one_digit(-10));

  EXPECT_EQ(1, keep_one_digit(1));
  EXPECT_EQ(1, keep_one_digit(-11));
}

TEST(example, pattern)
{
  Pattern sut({0,1,0,-1}, 2);

  ASSERT_EQ(0, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(-1, sut());
}
TEST(example, verify_first_line)
{
  Pattern sut({0,1,0,-1}, 1);

  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
}

TEST(phase, example)
{
  ASSERT_EQ(signal("48226158"), 
            phase("12345678", vector<int>{0, 1, 0, -1}));

  ASSERT_EQ(signal("34040438"), 
            phase("48226158", vector<int>{0, 1, 0, -1}));
}
