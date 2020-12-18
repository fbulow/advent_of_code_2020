#include <gtest/gtest.h>
#include "main.cpp"

TEST(eval, number)
{
 // EXPECT_EQ(1, eval("1"));
}

TEST(eval, add)
{
 EXPECT_EQ(5, eval("2 + 3"));
 EXPECT_EQ(18, eval("8 + 5 + 5"));
}

TEST(eval, multiplication)
{
 EXPECT_EQ(6, eval("2 * 3"));
}

TEST(eval, mixed)
{
  EXPECT_EQ(71, eval("1 + 2 * 3 + 4 * 5 + 6"));
  //  EXPECT_EQ(71, eval("13 * 5 + 6"));
  
}
