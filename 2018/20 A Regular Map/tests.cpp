#include <gtest/gtest.h>
#include "main.cpp"


TEST(minSteps, empty)
{
  ASSERT_EQ(0, minSteps("$^"));
}

TEST(minSteps, one)
{
  ASSERT_EQ(1, minSteps("$N^"));
}


TEST(char_type, isBeginning)
{
  EXPECT_TRUE(isBeginning('^'));
  EXPECT_TRUE(isBeginning('('));

  EXPECT_FALSE(isBeginning(')'));
  EXPECT_FALSE(isBeginning('$'));

  EXPECT_FALSE(isBeginning('N'));
  EXPECT_FALSE(isBeginning('S'));
  EXPECT_FALSE(isBeginning('E'));
  EXPECT_FALSE(isBeginning('W'));
}


TEST(char_type, isEnd)
{
  EXPECT_FALSE(isEnd('^'));
  EXPECT_FALSE(isEnd('('));

  EXPECT_TRUE(isEnd(')'));
  EXPECT_TRUE(isEnd('$'));

  EXPECT_FALSE(isEnd('N'));
  EXPECT_FALSE(isEnd('S'));
  EXPECT_FALSE(isEnd('E'));
  EXPECT_FALSE(isEnd('W'));
}

TEST(char_type, isMove)
{
  EXPECT_FALSE(isMove('^'));
  EXPECT_FALSE(isMove('('));

  EXPECT_FALSE(isMove(')'));
  EXPECT_FALSE(isMove('$'));

  EXPECT_TRUE(isMove('N'));
  EXPECT_TRUE(isMove('S'));
  EXPECT_TRUE(isMove('E'));
  EXPECT_TRUE(isMove('W'));
}

TEST(minSteps, one_paren)
{
  ASSERT_EQ(1, minSteps("$(N)^"));
}

TEST(isBranched, all)
{
  EXPECT_FALSE(isBranched(""));
  EXPECT_TRUE(isBranched("|"));
}

TEST(minSteps, branches)
{
  EXPECT_EQ(0, minSteps("N|"));
  EXPECT_EQ(0, minSteps("|S"));
  EXPECT_EQ(1, minSteps("N|S"));
  EXPECT_EQ(1, minSteps("N|SEE"));
}
