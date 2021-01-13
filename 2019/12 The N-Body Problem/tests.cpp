#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Coord, print)
{
  Moon sut;
  istringstream("<x=-1, y=7, z=3>")>>sut;
  EXPECT_EQ(sut.pos[0], -1);
  EXPECT_EQ(sut.pos[1],  7);
  EXPECT_EQ(sut.pos[2],  3);
  
  ostringstream out;
  out<<sut;
  EXPECT_EQ("-1, 7, 3 | 0, 0, 0", out.str());
}

TEST(Jupiter, updateVelocity)
{
  Jupiter sut(EXAMPLE);
  sut.updateVelocity();
  EXPECT_EQ(3,  sut.moons[0].vel[0]);
  EXPECT_EQ(-1, sut.moons[0].vel[1]);
  EXPECT_EQ(-1, sut.moons[0].vel[2]);
    
  sut.updatePosition();

  EXPECT_EQ(2,  sut.moons[0].pos[0]);
  EXPECT_EQ(-1, sut.moons[0].pos[1]);
  EXPECT_EQ(1,  sut.moons[0].pos[2]);
  


}

// TEST(solution, a)
// {
//   auto ans = solutionA(ifstream(INPUT));
//   //  EXPECT_EQ(2016, ans);
//   cout<<"Solution a: "<<ans<<endl;
  
// }

