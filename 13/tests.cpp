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

  vector<long int> const wait {0,1,4,6,7};
  EXPECT_EQ(wait, sut.wait);
}

TEST(sovlesB, example)
{
  Plan sut(ifstream{EXAMPLE});
  EXPECT_TRUE(sovlesB(sut, 1068781));
  EXPECT_FALSE(sovlesB(sut, 1068780));
}

TEST(solve, a)
{
  EXPECT_EQ(295, solveA(EXAMPLE));
  cout<<"Solution a: "<<solveA(INPUT)<<endl;
}

TEST(arrivalRequirement, first)
{
  Plan sut(ifstream{EXAMPLE});
  EXPECT_TRUE(sut.arrivalRequirement(1068781));
  EXPECT_FALSE(sut.arrivalRequirement(1068780));
}

TEST(solve, b)
{
  ASSERT_EQ(1068781,
	    solveB(EXAMPLE));
  cout<<"Solution b: "<<solveB(INPUT)<<endl;
}

TEST(MagicTimeBuilder, a)
{
  MagicTimeBuilder sut;
  sut.addBus(7,0);
  EXPECT_EQ(0, sut.candidate);
  sut.addBus(13,1);
  EXPECT_EQ(77, sut.candidate);
  sut.addBus(59,4);
  sut.addBus(31,6);
  sut.addBus(19,7);
  
  EXPECT_EQ(1068781, sut.candidate);
}
