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

TEST(getInput, example)
{
  auto const sut = getInput(EXAMPLE);
  EXPECT_EQ(5, sut.size());
  EXPECT_EQ(3, sut[0].size());
  EXPECT_EQ(3, sut[1].size());
  EXPECT_EQ(3, sut[2].size());
  EXPECT_EQ(1, sut[3].size());
  EXPECT_EQ(1, sut[4].size());

  EXPECT_EQ(1, sut[4].size());
  
  EXPECT_TRUE(sut[4].contains('b'));
}

TEST(solution, example)
{
  EXPECT_EQ(11, solution(getInput(EXAMPLE)));
}

TEST(solution_a, input)
{
  EXPECT_NE(6589, solution(getInput(INPUT)));//Error, assuming no newline on last line of input.
  EXPECT_EQ(6596, solution(getInput(INPUT)));
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

TEST(getInputB, example)
{
  auto const sut = getInputB(EXAMPLE);
   EXPECT_EQ(5, sut.size());
   EXPECT_EQ(3, sut[0].size());
   EXPECT_EQ(0, sut[1].size());
   EXPECT_EQ(1, sut[2].size());
   EXPECT_EQ(1, sut[3].size());
   EXPECT_EQ(1, sut[4].size());
}

TEST(solution_b, example)
{
  EXPECT_EQ(6, solution(getInputB(EXAMPLE)));
}


TEST(solution_b, input)
{
  EXPECT_EQ(3219, solution(getInputB(INPUT)));
}

/**/
