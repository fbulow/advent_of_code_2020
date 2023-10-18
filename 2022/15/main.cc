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

optional<Int> findDarkSpot(OnOff onOff, Int a, Int b)
{
  onOff[a];
  onOff[b];
  auto end = onOff.find(b);

  int sensors{0};
  auto inIntervall = [a,b](auto x){return (x>=a) and (x<=b);};

  for(auto const &x: onOff)
    {
      sensors+=x.second;
      if(sensors==0 and inIntervall(x.first))
	return {x.first};
    }
  return nullopt;
}

unsigned long long int tuningFrequency(unsigned long long int x, unsigned long long int y)
{
  return 4000000*x+y;
}

auto solutionB(vector<Sensor> const &sensors, Int minVal, Int maxVal)
{
  for(Int row = minVal; row<=maxVal; row++)
    {
      auto ret = findDarkSpot(getOnOff(sensors, row), minVal, maxVal);
      if(ret)
	return tuningFrequency(ret.value(), row);
    }
  assert(false);
}

auto solutionB(string filename, Int minVal, Int maxVal)
{
  return solutionB(getData(filename), minVal, maxVal);
}

TEST(solutionB, input)
{
  EXPECT_THAT(solutionB(INPUT, 0, 4000000),
	      Eq(13673971349056));
}

TEST(tuningFrequency, something_large)
{
  EXPECT_THAT(tuningFrequency(3418492, 3349056),
	    Eq(13673971349056));
}


TEST(solutionB, example)
{
  EXPECT_THAT(solutionB(EXAMPLE, 0, 20),
	      Eq(56000011));
}

TEST(findDarkSpot, last_is_dark)
{
  OnOff s;
  s.insert({-1, 1});
  s.insert({20, -1});
  EXPECT_THAT(findDarkSpot(s, 0,20).value(), Eq(20));
}

TEST(findDarkSpot, first_is_dark)
{
  OnOff s;
  s.insert({1, 1});
  EXPECT_THAT(findDarkSpot(s, 0,20).value(), Eq(0));
}

TEST(findDarkSpot, no_dark_spot)
{
  OnOff s;
  s.insert({-1, 1});
  s.insert({21, -1});
  EXPECT_FALSE(findDarkSpot(s, 0,20));
}

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
  ifstream in((EXAMPLE));
  auto sut = Sensor(in);

  EXPECT_THAT(sut.x, Eq(2));
  EXPECT_THAT(sut.y, Eq(18));
  EXPECT_THAT(sut.r, Eq(7));
}
