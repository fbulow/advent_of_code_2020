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


TEST(Cube, contains)
{
  Cube const sut({0,2}, {0,2}, {0,2});
  //  EXPECT_TRUE(sut.contains({1,1,1}));

}
