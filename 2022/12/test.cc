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

TEST(Input, canMoveFromTo)
{
  Coord from{0,0};
  Coord to{0,1};

  Input sut(vector<string>{"01"});
  EXPECT_TRUE(sut.canMoveFromTo(from, to));
}

TEST(Input, canMoveFromTo_because_are_equal)
{
  Coord from{0,0};
  Coord to{0,1};
  
  Input sut(vector<string>{"11"});
  EXPECT_TRUE(sut.canMoveFromTo(from, to));
}

TEST(Input, canMoveFromTo_is_false)
{
  Coord from{0,0};
  Coord to{0,1};
  
  Input sut(vector<string>{"02"});
  EXPECT_FALSE(sut.canMoveFromTo(from, to));
}

TEST(Coord, adjacent)
{
  auto sut = Coord{0,0}.adjacent();
  EXPECT_EQ(4, sut.size());
  EXPECT_THAT(sut, Contains(Coord( 1, 0)));
  EXPECT_THAT(sut, Contains(Coord( 0, 1)));
  EXPECT_THAT(sut, Contains(Coord(-1, 0)));
  EXPECT_THAT(sut, Contains(Coord( 0,-1)));
}
