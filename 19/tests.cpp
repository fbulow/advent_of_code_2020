#include <gtest/gtest.h>
#include "main.cpp"

TEST(rule, ctor_known)
{
  EXPECT_FALSE(Rule("0: 8 11").known());
  EXPECT_TRUE(Rule("72: \"b\"").known());
}

TEST(rule, ctor_left)
{
  Rule sut("0: 8 11");

  EXPECT_EQ(2, sut.left.size());
  EXPECT_EQ(8, sut.left[0]);
  EXPECT_EQ(11, sut.left[1]);

  EXPECT_EQ(0, sut.right.size());

}

TEST(rule, ctor_right)
{
  Rule sut("123: 72 | 52 121");
  EXPECT_EQ(1, sut.left.size());
  EXPECT_EQ(72, sut.left[0]);

  EXPECT_EQ(2, sut.right.size());
  EXPECT_EQ(52, sut.right[0]);
  EXPECT_EQ(121, sut.right[1]);
  
}
