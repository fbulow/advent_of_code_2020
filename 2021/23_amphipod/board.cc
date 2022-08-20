#include "board.hh"

#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

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
