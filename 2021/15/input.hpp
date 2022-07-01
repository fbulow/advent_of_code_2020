#pragma once
#include "cavern.hpp"
using namespace std;

using Data = Cavern;
Data input(istream& cin)
{
  string s;
  vector<string> data;
  cin>>s;
  while(not cin.eof())
    {
      data.push_back(s);
      cin>>s;
    }
  return {data};
}

Data example()
{
  istringstream in(
                   "1163751742\n"
                   "1381373672\n"
                   "2136511328\n"
                   "3694931569\n"
                   "7463417111\n"
                   "1319128137\n"
                   "1359912421\n"
                   "3125421639\n"
                   "1293138521\n"
                   "2311944581\n"
                   );
  return input(in);

}

TEST(input, all)
{
  auto sut = example();
  
  EXPECT_EQ(10, sut.Nrows());
  EXPECT_EQ(10, sut.Ncols());
  
  EXPECT_EQ(1, sut[Coord(0,0)]);
  EXPECT_EQ(3, sut[Coord(1,1)]);
  EXPECT_EQ(6, sut[Coord(0,2)]);
  EXPECT_EQ(8, sut[Coord(9,8)]);
}



