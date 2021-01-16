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

TEST(Moon, energy)
{
  Jupiter sut(EXAMPLE);
  sut.step(10);
  
  EXPECT_EQ(36,
            sut.moons[0].energy());
  EXPECT_EQ(45,
            sut.moons[1].energy());
  EXPECT_EQ(80,
            sut.moons[2].energy());
  EXPECT_EQ(18,
            sut.moons[3].energy());

  EXPECT_EQ(179, sut.energy());
}

TEST(solution, a)
{
  auto ans = solutionA(INPUT);
  cout<<"Solution a: "<<ans<<endl;
  
}


TEST(solution, b)
{
  auto ans = solutionB(Jupiter(INPUT));
  EXPECT_EQ(402951477454512, ans);
  cout<<"Solution b: "<<ans<<endl;
}

