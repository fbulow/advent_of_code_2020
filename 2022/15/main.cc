#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "impl.hh"

#include <fstream>
#include <ctype.h>
#include <cmath>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace testing;



TEST(crapOnRow, example)
{
  EXPECT_THAT(crapOnRow(getData(EXAMPLE), 10), Eq(1));
}

TEST(solutionA, input)
{
  EXPECT_THAT(solutionA(INPUT, 2000000), Eq(5335787));
}


TEST(solutionA, example)
{
  EXPECT_THAT(solutionA(EXAMPLE, 10), Eq(26));
}
     

TEST(getData, example)
{
  auto sut = *getData(EXAMPLE).rbegin();
  EXPECT_THAT(sut.x, Eq(20));
  EXPECT_THAT(sut.y, Eq(1));
}

TEST(read, example_dots)
{
  ifstream in(EXAMPLE);
  auto sut = Sensor(in);

  EXPECT_THAT(sut.x, Eq(2));
  EXPECT_THAT(sut.y, Eq(18));
  EXPECT_THAT(sut.r, Eq(7));
}
