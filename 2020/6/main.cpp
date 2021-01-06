#include"main.hpp"
#include <gtest/gtest.h>



TEST(getRawInput, first)
{
  EXPECT_EQ(15, getRawInput(EXAMPLE).size());
}

TEST(group, first)
{
  EXPECT_EQ(5, group(getRawInput(EXAMPLE)).size());
}

TEST(Ans, intersectWith)
{
  Ans a;
  a = Ans("abd");
  EXPECT_EQ(2, Ans{"abc"}.intersectWith(Ans{"bcd"}).size());
}

TEST(Ans, unionWidth)
{
  Ans a;
  a = Ans("abd");
  EXPECT_EQ(4, Ans{"abc"}.unionWith(Ans{"bcd"}).size());
}

TEST(toAns, first)
{
  EXPECT_EQ(3, Ans("abc").size());
  EXPECT_EQ(0, Ans("").size());
}

TEST(stringIntersection, first)
{
  
  EXPECT_EQ(3, stringIntersection(Ans("abc"), "abc").size());
  EXPECT_EQ(3, stringIntersection(Ans("abc"), "abcd").size());
  EXPECT_EQ(2, stringIntersection(Ans("abc"), "ab").size());
}

TEST(getInputB, examplea)
{
  EXPECT_EQ(3, reduceIntersect({{"abc"}}).size());
  EXPECT_EQ(0, reduceIntersect({{"a"},
				{"b"},
				{"c"}}).size());
  EXPECT_EQ(1, reduceIntersect({{"ab"},
				{"ac"},
				}).size());
  EXPECT_EQ(1, reduceIntersect({{"a"},
				{"a"},
				{"a"},
				{"a"},
				}).size());

  EXPECT_EQ(1, reduceIntersect({{"b"}}).size());
}

TEST(solution, a)
{
  EXPECT_EQ(11, reduceAndCount(EXAMPLE, reduceUnion));
  EXPECT_EQ(6596, reduceAndCount(INPUT, reduceUnion));
}

TEST(solution, b)
{
  EXPECT_EQ(6, reduceAndCount(EXAMPLE, reduceIntersect));
  EXPECT_EQ(3219, reduceAndCount(INPUT, reduceIntersect));
  
}



