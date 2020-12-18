#include <gtest/gtest.h>
#include "main.cpp"

TEST(eval, number)
{
 EXPECT_EQ(1, eval("1"));
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

TEST(parenthesis, value)
{
  EXPECT_EQ(8,  eval("(8)"));
  EXPECT_EQ(51, eval("1 + (2 * 3) + (4 * (5 + 6))"));
  
}

TEST(given, other_cases)
{

  EXPECT_EQ(26,     eval("2 * 3 + (4 * 5)"));
  EXPECT_EQ(437,    eval("5 + (8 * 3 + 9 + 3 * 4 * 3)"));
  EXPECT_EQ(12240,  eval("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"));
  EXPECT_EQ(13632,  eval("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"));


}


TEST(solve, a)
{
  auto ans = solveA(INPUT);
  ASSERT_GT(ans, 1000557957);
  cout<<"Solution a: "<<ans<<endl;
}

TEST(evalB, examples)
{
  EXPECT_EQ(231,
	    evalB("1 + 2 * 3 + 4 * 5 + 6"));
  
  EXPECT_EQ(51,		evalB("1 + (2 * 3) + (4 * (5 + 6))"));
  EXPECT_EQ(46,		evalB("2 * 3 + (4 * 5)"));
  EXPECT_EQ(1445,	evalB("5 + (8 * 3 + 9 + 3 * 4 * 3)"));
  EXPECT_EQ(669060,	evalB("5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))"));
  EXPECT_EQ(23340,	evalB("((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2"));
}

TEST(solve, b)
{
  auto ans = solveB(INPUT);
  cout<<"Solution b: "<<ans<<endl;
}
