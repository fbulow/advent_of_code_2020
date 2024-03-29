#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include "read_input.hh"
#include <algorithm>
#include "height.hh"
#include "steps.hh"

using namespace testing;
using namespace std;


class StepsB: public Steps{
public:
  StepsB(Input &&in_)
    :Steps(move(in_))
  {}
  bool isEnd(char c) const override
  {return c == 'a';}

};

int solutionA(Steps &s)
{
  try
    {
      int i = 0;
      while(true)
	s.stepFrom(i++);
    }
  catch(Answer const &a)
    {
      return a.value;
    }
}
int solutionA(Steps &&s)
{
  Steps cache=move(s);
  return solutionA(cache);
}

TEST(solutionB, input)
{
  ifstream in(INPUT);
  StepsB data(readInput(in));

  EXPECT_THAT(solutionA(data), Eq(399));
}


TEST(solutionB, example)
{
  ifstream in(EXAMPLE);
  StepsB data(readInput(in));

  EXPECT_THAT(solutionA(data), Eq(29));
}


TEST(solutionA, input)
{
  ifstream in(INPUT);
  EXPECT_THAT(solutionA(readInput(in)), Eq(408));

}

TEST(solutionA, example)
{
  ifstream in(EXAMPLE);
  EXPECT_THAT(solutionA(readInput(in)), Eq(31));

}

TEST(Steps, climbOk)
{
  ifstream in(EXAMPLE);
  auto sut = Steps(readInput(in));

  EXPECT_TRUE(sut.climbOk(1,0,0,0));
  EXPECT_FALSE(sut.climbOk(0,3,0,2));

}

TEST(readInput, example)
{
  ifstream in(EXAMPLE);
  auto sut = readInput(in);

  EXPECT_THAT(sut[0], Eq("Sabqponm"));
  EXPECT_THAT(sut[1], Eq("abcryxxl"));
  EXPECT_THAT(sut[2], Eq("accszExk"));
  EXPECT_THAT(sut[3], Eq("acctuvwj"));
  EXPECT_THAT(sut[4], Eq("abdefghi"));
  EXPECT_THAT(sut.size(), Eq(5));
}
