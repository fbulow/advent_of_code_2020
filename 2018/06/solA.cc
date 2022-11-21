#include<numeric>
#include<vector>
#include<ranges>
#include<set>
#include<algorithm>

#include"board.hh"
#include"input.hh"

class solA
{
public:
  int ans{0};
  solA(Data const d)
    :solA(Board(d))
  {}

  solA(Board b)
  {
    b.fill();
    ans = b.sizeOfLargestFiniteRegion();
  }
};
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(example, a)
{
  ASSERT_THAT(solA(Input::example()).ans, Eq(17));
}

