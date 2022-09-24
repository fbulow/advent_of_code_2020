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

namespace A{
  Column burrow()
  {
    return {2};
  }
}


TEST(Board, apply_move_where_from_is_set)
{
  Board b;
  b.put(0,{'A'});
  auto sut = b.apply({0,1});
  EXPECT_THAT(sut.getTop(0), Eq('.'));
  EXPECT_THAT(sut.getTop(1), Eq('A'));
}

TEST(Board, different_columns_have_different_values)
{
  Board sut;
  sut.put(0,{'A'});

  EXPECT_THAT(sut.getTop(0), Eq('A'));
  EXPECT_THAT(sut.getTop(10), Eq('.'));
}

TEST(Board, two_amphipods_in_a_space_one_leaves_the_other_is_on_top)
{
  Space sut;
  sut.put({'A'});
  sut.put({'B'});
  sut.pop();
  ASSERT_THAT(sut.getTop(), Eq('A'));
}

TEST(A_Board, burrow_returns_a_burrow)
{
  Board sut;
  ASSERT_TRUE(sut.isBurrow(A::burrow()));
}

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

TEST(Board, put_coridor_and_get)
{
  Board sut;
  sut.put(0, 'A');
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

TEST(Boad, pop_from_corridor)
{
  Board sut;
  sut.put(0, 'A');
  sut.pop(0);
  EXPECT_THAT(sut.getTop(0), Eq('.'));
}

TEST(Space, empty_if_only_residents)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.getTop(), Eq('.'));
  sut.put('A');
  ASSERT_THAT(sut.getTop(), Eq('.'));
}

TEST(Space, depth_reduced_when_adding_resident_to_empty)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.depth(),Eq(2));
  sut.put('A');
  ASSERT_THAT(sut.depth(),Eq(1));
}

TEST(Space, depth_reduced_when_adding_non_resident_to_empty)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.depth(),Eq(2));
  sut.put('B');
  ASSERT_THAT(sut.depth(),Eq(1));
}
