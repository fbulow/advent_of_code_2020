#include <gtest/gtest.h>
#include "dice.hh"
#include "player.hh"

TEST(Player, move)
{
  Player sut(1);
  sut.move(2);
  EXPECT_EQ(3, sut.pos());
  sut.move(8);// 11 does not exist.
  EXPECT_EQ(1, sut.pos());  
}

TEST(Player, score)
{
  Player sut(1);
  sut.move(2);
  EXPECT_EQ(3, sut.score());
}

TEST(Dice, count)
{
  {
    Dice sut;
    EXPECT_EQ(0,sut.count());
    sut.roll();
    EXPECT_EQ(1,sut.count());
  }
  {
    Dice sut(0,100);
    EXPECT_EQ(100,sut.count());
  }
  
}


TEST(Dice, roll)
{
  {
    Dice sut;
    EXPECT_EQ(6, sut.rollTrice());
    EXPECT_EQ(15, sut.rollTrice());
  }
  {
    Dice sut;
    EXPECT_EQ(1, sut.roll());
    EXPECT_EQ(2, sut.roll());
  }
  {
    Dice sut(9);
    EXPECT_EQ(9, sut.roll());
    EXPECT_EQ(10, sut.roll());
  }
  {
    Dice sut(100);
    EXPECT_EQ(100, sut.roll());
    EXPECT_EQ(1, sut.roll());
  }
    
}
