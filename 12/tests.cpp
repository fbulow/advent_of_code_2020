#include <gtest/gtest.h>
#include "main.cpp"

using Room = vector<string>;

TEST(get, Instruction)
{
  Inst sut;
  istringstream in("F10");
  in>>sut;

  EXPECT_EQ('F', sut.cmd);
  EXPECT_EQ(10 , sut.arg);
}

TEST(get, input)
{
  Instructions sut(INPUT);
  EXPECT_EQ(790, sut.size());
  
}

TEST(Ship, rotate)
{
  Ship sut;
  EXPECT_EQ('E', sut.direction());

  sut.apply(Inst{'L', 90});
  EXPECT_EQ('N', sut.direction());

  sut.apply(Inst{'L', 90});
  EXPECT_EQ('W', sut.direction());

  sut.apply(Inst{'L', 90});
  EXPECT_EQ('S', sut.direction());

  sut.apply(Inst{'R', 90});
  EXPECT_EQ('W', sut.direction());
}

TEST(Ship, initial_position)
{
  Ship sut;
  EXPECT_EQ(Pos(0,0), sut.pos());
}

TEST(Pos, step)
{
  EXPECT_EQ(Pos(-1,0),
	    step(Pos(0,0), 'N', 1));
  EXPECT_EQ(Pos( 1,0),
	    step(Pos(0,0), 'S', 1));
  EXPECT_EQ(Pos( 0,-1),
	    step(Pos(0,0), 'W', 1));
  EXPECT_EQ(Pos( 0,1),
	    step(Pos(0,0), 'E', 1));

}
