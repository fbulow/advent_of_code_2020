#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Cell, all)
{
  {
    Cell sut;
    EXPECT_EQ(0, sut.count());
    sut++;
    EXPECT_EQ(1, sut.count());    
  }


  {
    //If a cube is active and exactly 2 or 3 of its neighbors are also
    //active, the cube remains active. Otherwise, the cube becomes
    //inactive.

    int i=0;
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    ASSERT_EQ(2, i);
    EXPECT_TRUE(Cell(true, i++).becomesActive());
    ASSERT_EQ(3, i);
    EXPECT_TRUE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());
    EXPECT_FALSE(Cell(true, i++).becomesActive());

  }

  {
    //If a cube is inactive but exactly 3 of its neighbors are active,
    //the cube becomes active. Otherwise, the cube remains inactive.

    int i=0;
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    ASSERT_EQ(3, i);
    EXPECT_TRUE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
    EXPECT_FALSE(Cell(false, i++).becomesActive());
  }
}

TEST(Conway, ctor)
{
  {
    Conway<3> sut({
        ".#.",
        "..#",
        "###"});

    EXPECT_EQ(5, sut.countActive());
  }
  {
    Conway<3> sut(EXAMPLE);
    EXPECT_EQ(5, sut.countActive());
  }

}

TEST(solution, a)
{
  ASSERT_EQ(112, solutionA(EXAMPLE));
  cout<<"Solution a: "<<solutionA(INPUT)<<endl;
}

TEST(solution, b)
{
  ASSERT_EQ(848, solutionB(EXAMPLE));
  cout<<"Solution b: "<<solutionB(INPUT)<<endl;
}

TEST(adjecent, Nthree)
{
  //Each cube only ever considers its neighbors: any of the 26 other
  //cubes where any of their coordinates differ by at most 1. For
  //example, given the cube at x=1,y=2,z=3, its neighbors include the
  //cube at x=2,y=2,z=2, the cube at x=0,y=2,z=3, and so on.

  {
    auto a = Coord<3>({0,0,0});
    auto b = Coord<3>({0,0,0});

    ASSERT_TRUE(a==b);
  }
  {
    auto a = Coord<3>({0,0,1});
    auto b = Coord<3>({0,0,0});

    ASSERT_FALSE(a==b);
  }

  
  auto sut = adjecent(Coord<3>({0,0,0}));
  EXPECT_EQ(sut.end(), find(sut.begin(), sut.end(), Coord<3>({0,0,0})));
  EXPECT_EQ(26, sut.size());
  EXPECT_TRUE(all_of(sut.begin(), sut.end(),
                     [](auto &x)
                     {
                       return all_of(x.data.begin(),
                                     x.data.end(),
                                     [](auto q)
                                     {
                                       return (q==-1) or (q==0) or (q==1);
                                     });
                     }));
                                     
  
}
