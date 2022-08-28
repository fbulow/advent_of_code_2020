#include "board.hh"

bool Board::isBurrow(Column c) const
{
  switch(c)
    {
    case 2:
    case 4:
    case 6:
    case 8:
      return true;
    default:
      return false;
    }
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;



TEST(Board, has_ten_times_nine_valid_moves)
{
  Board sut;
  EXPECT_THAT(sut.moves().size(), Eq(55));
  EXPECT_THAT(sut.moves(), Contains(Move{0,2}));
}


TEST(Board, increase_score_when_applying_move)
{
  struct :Board
  {
    Result steps(Move) const override {
      return 5;
    }
  } sut;


  EXPECT_THAT(sut.score(), Eq(0));
  EXPECT_THAT(sut.steps(A::Move{}), Eq(5));
  ASSERT_THAT(sut.apply(A::Move{}).score(), Eq(5));
}

TEST(Board, get_empty_space)
{
  Board sut;
  EXPECT_THAT(sut.getTop(0), Eq('.'));
}

TEST(Board, set_coridor_and_get)
{
  Board sut;
  sut.set(0, 'A');
  EXPECT_THAT(sut.getTop(0), Eq('A'));
}

TEST(Board, column_is_burrow_all_cases)
{
  Board sut;
  EXPECT_FALSE(sut.isBurrow(0));
  EXPECT_FALSE(sut.isBurrow(1));
  EXPECT_TRUE (sut.isBurrow(2));
  EXPECT_FALSE(sut.isBurrow(3));
  EXPECT_TRUE (sut.isBurrow(4));
  EXPECT_FALSE(sut.isBurrow(5));
  EXPECT_TRUE (sut.isBurrow(6));
  EXPECT_FALSE(sut.isBurrow(7));
  EXPECT_TRUE (sut.isBurrow(8));
  EXPECT_FALSE(sut.isBurrow(9));
  EXPECT_FALSE(sut.isBurrow(10));
}
