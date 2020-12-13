#include <gtest/gtest.h>
#include "main.cpp"

using Room = vector<string>;

TEST(find, departure)
{
  EXPECT_FALSE(  departure(939,
			 {7,13,59,31,19}) );
  EXPECT_TRUE(  departure(944,
			 {7,13,59,31,19}) );
}

TEST(find, nextAvaliableTime)
{
  EXPECT_EQ(944, nextAvaliableTime(939,
				   {7,13,59,31,19}) );
}


TEST(Plan, ctor)
{
  Plan sut(ifstream{EXAMPLE});
  EXPECT_EQ(939, sut.arrival);
  vector<long int> const times {7,13,59,31,19};
  EXPECT_EQ(times, sut.times);
  
}

TEST(solve, a)
{
  EXPECT_EQ(295, solveA(EXAMPLE));
  cout<<"Solution a: "<<solveA(INPUT)<<endl;
}
