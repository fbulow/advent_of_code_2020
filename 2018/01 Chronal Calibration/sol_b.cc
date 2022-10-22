#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<fstream>

using namespace testing;


#include"firstRepeating.hh"

TEST(b, example)
{
  EXPECT_THAT(
	      firstRepeating({1, -1}),
	      Eq(0));
  EXPECT_THAT(
	      firstRepeating({+3, +3, +4, -2, -4}),
	      Eq(10));
}

TEST(b, solution)
{
  ifstream in(INPUT);
  vector<int> data;
  int nxt;
  in>>nxt;
  while(not in.eof())
    {
      data.push_back(nxt);
      in>>nxt;
    }
  
  EXPECT_THAT(
	      firstRepeating(data),
	      Eq(57538));
}
