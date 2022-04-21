#include <gtest/gtest.h>
#include<algorithm>
#include<fstream>
#include"cube.hh"
#include"instruction.hh"
#include"space.hh"
#include<list>

#include"square_space.hh"
#include"cube.hh"

using namespace std;

TEST(Cube, splitBy)
{
  auto sut = Cube(
      {0,3},
      {0,3},
      {0,3});

    auto cut = Cube(
	{1,1},
	{1,1},
	{1,1});

    
    EXPECT_EQ(27, sut.splitBy(cut).size());

}
