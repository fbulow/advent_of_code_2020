#include "board.hh"
Board::Board(std::string_view vi)
  :Board(4)
{
  assert(isValidVisual(vi));
  for(int i=0;i<11;i++)
    if(isBurrow(i))
      readColumn(vi, i);
    else
      put(i, vi[14+i]);
}

Board::Board(int depth)
{
  char c='A';
  for(size_t i=0;i<11;i++)
    if(isBurrow(i))
      {
	assert(burrow(c) == i);
	spaces[i] = Space(depth,c++);
      }
    else
      spaces[i] = Space(1);
}
size_t Board::burrow(Amphipod a) const
{
  switch(a)
    {
    case'A': return 2;
    case'B': return 4;
    case'C': return 6;
    case'D': return 8;
    }
  assert(false);
}


Board Board::failed()
{
  Board ret(0);
  ret.score_ = Result();
  return ret;
}


bool Board::isValidVisual(string_view vi) const
{
  //"#############"    
  //"#...........#"
  //"###.#.#.#.###"
  //"  #.#.#.#.#  "
  //"  #.#.#.#.#  "
  //"  #.#.#.#.#  "
  //"  #########  "
  if (vi.size()!=91) return false;
  for(size_t i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 25, 26, 27, 28, 30, 32, 34, 36, 37, 38, 41, 43, 45, 47, 49, 54, 56, 58, 60, 62, 67, 69, 71, 73, 75, 80, 81, 82, 83, 84, 85, 86, 87, 88})
    if(vi[i]!='#') return false;
  for(size_t i : {39, 40, 50, 51, 52, 53, 63, 64, 65, 66, 76, 77, 78, 79, 89, 90, 39, 40, 50, 51, 52, 53, 63, 64, 65, 66, 76, 77, 78, 79, 89, 90})
    if(vi[i]!=' ') return false;
  return true;
}

bool Board::isDone() const
{
  for(int i=0;i<11;i++)
    if (not spaces[i].isDone())
      return false;
  return true;
}
 
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
  auto sut = b.apply({0,2});
  EXPECT_THAT(sut.getTop(0), Eq('.'));
  EXPECT_THAT(sut.getTop(2), Eq('A'));
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
  Space sut(2);
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

TEST(swapOk, A_to_dorm_type_A_with_an_B_in_there)
{
  // Not ok to move A to home when there is something else there
  
  auto a = Space(1); a.put('A');
  auto b = Space(2, 'A'); b.put('B');

  ASSERT_FALSE(swapOk(a,b)); // Move from a->b
}

TEST(space, is_hallway_or_not)
{
  EXPECT_TRUE(Space(1).isHallway());
  EXPECT_FALSE(Space(2).isHallway());
}

TEST(swapOk, not_ok_to_move_from_hallway_to_hallway)
{
  auto a = Space(1); a.put('A');
  auto b = Space(1);
  
  ASSERT_FALSE(swapOk(a,b)); // Move from a->b
}

TEST(Space, hallway_isDone)
{
  Space sut(1);
  EXPECT_TRUE (sut.isDone());
  sut.put('A');
  EXPECT_FALSE(sut.isDone());
}


TEST(Board, isDone)
{
  Board sut;
  for(int i=0;i<4;i++)
    {
      sut.put(2, 'A');
      sut.put(4, 'B');
      sut.put(6, 'C');
      EXPECT_FALSE(sut.isDone());
      sut.put(8, 'D');
    }
  EXPECT_TRUE(sut.isDone());
}

TEST(Board, visual_ctor_empty)
{
    Board sut("#############"
	      "#...........#"
	      "###.#.#.#.###"
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #########  ");
    for(int i=0;i<11;i++)
      EXPECT_THAT(sut.getTop(i), Eq('.'));
}

TEST(Board, visual_ctor_first_burrow)
{
  Board sut("#############"
	    "#...........#"
	    "###A#.#.#.###"
	    "  #B#.#.#.#  "
	    "  #C#.#.#.#  "
	    "  #D#.#.#.#  "
	    "  #########  ");
  EXPECT_THAT(sut.getTop(2), Eq('A'));
  sut.pop(2);
  EXPECT_THAT(sut.getTop(2), Eq('B'));
  sut.pop(2);
  EXPECT_THAT(sut.getTop(2), Eq('C'));
  sut.pop(2);
  EXPECT_THAT(sut.getTop(2), Eq('D'));
  sut.pop(2);
  EXPECT_THAT(sut.getTop(2), Eq('.'));
}

TEST(Board, visual_ctor_second_burrow)
{
  Board sut("#############"
	    "#...........#"
	    "###.#A#.#.###"
	    "  #.#B#.#.#  "
	    "  #.#C#.#.#  "
	    "  #.#D#.#.#  "
	    "  #########  ");
  EXPECT_THAT(sut.getTop(4), Eq('A'));
  sut.pop(4);
  EXPECT_THAT(sut.getTop(4), Eq('B'));
  sut.pop(4);
  EXPECT_THAT(sut.getTop(4), Eq('C'));
  sut.pop(4);
  EXPECT_THAT(sut.getTop(4), Eq('D'));
  sut.pop(4);
  EXPECT_THAT(sut.getTop(4), Eq('.'));
}

TEST(Board, visual_ctor_third_burrow)
{
  Board sut("#############"
	    "#...........#"
	    "###.#.#A#.###"
	    "  #.#.#B#.#  "
	    "  #.#.#C#.#  "
	    "  #.#.#D#.#  "
	    "  #########  ");
  EXPECT_THAT(sut.getTop(6), Eq('A'));
  sut.pop(6);
  EXPECT_THAT(sut.getTop(6), Eq('B'));
  sut.pop(6);
  EXPECT_THAT(sut.getTop(6), Eq('C'));
  sut.pop(6);
  EXPECT_THAT(sut.getTop(6), Eq('D'));
  sut.pop(6);
  EXPECT_THAT(sut.getTop(6), Eq('.'));
}

TEST(Board, visual_ctor_fourth_and_last_burrow)
{
  Board sut("#############"
	    "#...........#"
	    "###.#.#.#A###"
	    "  #.#.#.#B#  "
	    "  #.#.#.#C#  "
	    "  #.#.#.#D#  "
	    "  #########  ");
  EXPECT_THAT(sut.getTop(8), Eq('A'));
  sut.pop(8);
  EXPECT_THAT(sut.getTop(8), Eq('B'));
  sut.pop(8);
  EXPECT_THAT(sut.getTop(8), Eq('C'));
  sut.pop(8);
  EXPECT_THAT(sut.getTop(8), Eq('D'));
  sut.pop(8);
  EXPECT_THAT(sut.getTop(8), Eq('.'));
}

TEST(Board, visual_first_hallways)
{
  {
    Board sut("#############"
	      "#A..........#"
	      "###.#.#.#.###"
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #########  ");
    EXPECT_THAT(sut.getTop(0), Eq('A'));
    sut.pop(0);
    EXPECT_THAT(sut.getTop(0), Eq('.'));
  }
  {
    Board sut("#############"
	      "#.A.........#"
	      "###.#.#.#.###"
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #########  ");
    EXPECT_THAT(sut.getTop(1), Eq('A'));
    sut.pop(1);
    EXPECT_THAT(sut.getTop(1), Eq('.'));
  }
  {
    Board sut("#############"
	      "#...A.......#"
	      "###.#.#.#.###"
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #########  ");
    EXPECT_THAT(sut.getTop(3), Eq('A'));
    sut.pop(3);
    EXPECT_THAT(sut.getTop(3), Eq('.'));
  }
  {
    Board sut("#############"
	      "#.....A.B.CD#"
	      "###.#.#.#.###"
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #.#.#.#.#  "
	      "  #########  ");
    EXPECT_THAT(sut.getTop(5), Eq('A'));
    EXPECT_THAT(sut.getTop(7), Eq('B'));
    EXPECT_THAT(sut.getTop(9), Eq('C'));
    EXPECT_THAT(sut.getTop(10), Eq('D'));

  }

}


TEST(Board, failed)
{
  auto const sut  = Board::failed();
  ASSERT_TRUE(sut.isDone());
  ASSERT_FALSE(sut.score());
}

TEST(costPerStep, all_cases)
{
  EXPECT_THAT(costPerStep('A'), Eq(1));
  EXPECT_THAT(costPerStep('B'), Eq(10));
  EXPECT_THAT(costPerStep('C'), Eq(100));
  EXPECT_THAT(costPerStep('D'), Eq(1000));
}

TEST(Board, move_to_corridor)
{
  Board sut("#############"
	    "#...........#"
	    "###B#C#B#D###"
	    "  #D#C#B#A#  "
	    "  #D#B#A#C#  "
	    "  #A#D#C#A#  "
	    "  #########  ");

  Move m{8,10};
  
  EXPECT_THAT(sut.steps(m),
	      Eq(3));
  
  EXPECT_THAT(sut.apply(m).score(), Eq(3000));
}


TEST(Board, illegalMoves)
{
  //                01234567890
  Board const sut("#############"
		  "#.........A.#"
		  "###.#.#.#.###"
		  "  #.#.#.#.#  "
		  "  #.#.#.#.#  "
		  "  #D#.#B#A#  "
		  "  #########  ");
  //                01234567890
  EXPECT_FALSE(sut.apply({0,1}).score()); // hall to hall
  EXPECT_FALSE(sut.apply({10,9}).score()); // hall to hall
  EXPECT_FALSE(sut.apply({2,4}).score()); // burrow to burrow
  EXPECT_FALSE(sut.apply({2,9}).score()); // to occupied burrow
  EXPECT_FALSE(sut.apply({4,9}).score()); // to wrong burrow
}

TEST(apply, move_is_not_swap)
{
  //                01234567890
  Board const sut("#############"
		  "#.........A.#"
		  "###.#.#.#.###"
		  "  #.#.#.#.#  "
		  "  #.#.#.#.#  "
		  "  #D#.#B#A#  "
		  "  #########  ");
  //                01234567890
  EXPECT_TRUE(sut.apply({2,3}).score());
  EXPECT_FALSE(sut.apply({3,2}).score());
}

TEST(swapOk, not_ok_because_burrow_is_of_wrong_type)
{
  Space burrow(2, 'A');
  Space hallway(1, '.');
  hallway.put('B');
  EXPECT_FALSE(swapOk(burrow, hallway));
}

TEST(Board, burrow__Amphipod_to_burrow_index_mapping)
{

  //                01234567890
  Board const sut("#############"
		  "#...........#"
		  "###.#.#.#.###"
		  "  #.#.#.#.#  "
		  "  #.#.#.#.#  "
		  "  #.#.#.#.#  "
		  "  #########  ");
  //                01234567890
  //                  A B C D

  EXPECT_THAT(sut.burrow('A'), Eq(2));
  EXPECT_THAT(sut.burrow('B'), Eq(4));
  EXPECT_THAT(sut.burrow('C'), Eq(6));
  EXPECT_THAT(sut.burrow('D'), Eq(8));
}
