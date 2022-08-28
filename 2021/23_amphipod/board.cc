#include "board.hh"

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
