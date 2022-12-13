#include "solA.hh"


#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(Coord, ctor)
{
  Coord sut(1,2);
  EXPECT_EQ(1, sut.row());
  EXPECT_EQ(2, sut.col());
}

TEST(Coord, up)
{
  Coord sut(1,2);

  EXPECT_EQ(0, sut.up().row());
  EXPECT_EQ(2, sut.up().col());
}

TEST(Coord, down)
{
  Coord sut(1,2);

  EXPECT_EQ(2, sut.down().row());
  EXPECT_EQ(2, sut.down().col());
}

TEST(Coord, left)
{
  Coord sut(1,2);

  EXPECT_EQ(1, sut.left().row());
  EXPECT_EQ(1, sut.left().col());
}

TEST(Coord, right)
{
  Coord sut(1,2);

  EXPECT_EQ(1, sut.right().row());
  EXPECT_EQ(3, sut.right().col());
}
