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


TEST(char_type, isBegining)
{
  EXPECT_TRUE(isBegining('^'));
  EXPECT_TRUE(isBegining('('));

  EXPECT_FALSE(isBegining(')'));
  EXPECT_FALSE(isBegining('$'));

  EXPECT_FALSE(isBegining('N'));
  EXPECT_FALSE(isBegining('S'));
  EXPECT_FALSE(isBegining('E'));
  EXPECT_FALSE(isBegining('W'));
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
}
