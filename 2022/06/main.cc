#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>

using namespace std;

auto solA(string const &s, int size=4)
{
  auto a = s.begin();
  auto b = next(a, size);
  while( b<s.end() )
    {
      set<char> scope{a,b};
      if(scope.size()==size)
	return distance(s.begin(), b);
      else
	{
	  a++;
	  b++;
	}
    }
}
  

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;
TEST(solA, example)
{
  EXPECT_THAT(solA("bvwbjplbgvbhsrlpgdmjqwftvncz")	, Eq(5));
  EXPECT_THAT(solA("nppdvjthqldpwncqszvftbrmjlhg")	, Eq(6));
  EXPECT_THAT(solA("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg")	, Eq(10));
  EXPECT_THAT(solA("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw")	, Eq(11));
}

TEST(solA, real)
{
  EXPECT_THAT(solA(getAllLines(INPUT)[0]), Eq(1909));
}

TEST(solB, real)
{
  EXPECT_THAT(solA(getAllLines(INPUT)[0],14), Eq(3380));
}

