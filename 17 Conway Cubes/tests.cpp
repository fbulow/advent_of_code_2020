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
    Conway sut({
        ".#.",
        "..#",
        "###"});

    EXPECT_EQ(5, sut.countActive());
  }
  {
    Conway sut(EXAMPLE);
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
  ASSERT_EQ(848, solutionA(EXAMPLE));
  cout<<"Solution b: "<<solutionA(INPUT)<<endl;
}

