#include <gtest/gtest.h>
#include<algorithm>
#include<fstream>
#include"cube.hh"
#include"instruction.hh"
#include"space.hh"
#include<list>

#include"square_space.hh"
using namespace std;



TEST(SquareSpace, countOn)
{
  {
    SquareSpace sut;
  
    Range one{0,0};
    sut.fill(Cube{one,one,one}, true);

    EXPECT_EQ(1, sut.countOn());
  }
  {
    SquareSpace sut;
  
    Range one{0,0};
    sut.fill(Cube{{0,1},one,one}, true);

    EXPECT_EQ(2, sut.countOn());
  }

}
  
