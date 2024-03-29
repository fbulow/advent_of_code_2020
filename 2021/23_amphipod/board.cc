#include "board.hh"

void Board::pop(Column c)
{
  spaces[c].pop();
}
void Board::put(Column c, Amphipod a)
{
  spaces[c].put(a);
}
Amphipod Board::getTop(Column c)const
{
  return spaces[c].getTop();
}

bool Board::isLegalMove(Move const & m) const
{
  if(m.from==m.to)
    return false;
  if(getTop(m.from)=='.')
    return false;
  else if(m.distance()>1)
    {
      if(any_of(
		next(spaces.begin(), m.min()+1),
		next(spaces.begin(), m.max()),
		[this](auto const &s)
		{
		  auto ret = s.corridorIsBlocked();
		  return ret;
		}))
	return false;
    }
  return spaces[m.from].canMoveTo(spaces[m.to]);
}

unsigned int costPerStep(Amphipod a)
{
  switch(a)
    {
    case 'A':
      return 1;
    case 'B':
      return 10;
    case 'C':
      return 100;
    case 'D':
      return 1000;
    }
  assert(false);
}


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

Result Board::steps(Move const&m) const
{
  return
    spaces[m.from].stepsToCorridor()+
    spaces[m.to].stepsToCorridor()+
    m.distance()
    +(spaces[m.from].isHallway()?0:1)
    ;
}

unsigned int Board::burrow(Amphipod a) const
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

vector<Move> Board::moves() const
{
  vector<Move> ret;
  for(unsigned int i=0;i<11;i++)
    {
      Amphipod a = getTop(i);
      if(a=='.')
	{} // Do nothing
      else
	{
	  Move straightHome(i, burrow(a));
	  if(isLegalMove(straightHome))
	    return {straightHome};
	}
      for(unsigned int j=0;j<11;j++)
	{
	  Move m{i,j};
	  if(isLegalMove(m))
	    ret.emplace_back(move(m));
	}
    }
  return ret;
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

TEST(space, is_hallway_or_not)
{
  EXPECT_TRUE(Space(1).isHallway());
  EXPECT_FALSE(Space(2).isHallway());
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
  //          01234567890
  Board sut("#############"
	    "#...........#"
	    "###B#C#B#D###"
	    "  #D#C#B#A#  "
	    "  #D#B#A#C#  "
	    "  #A#D#C#A#  "
	    "  #########  ");
  //          01234567890

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
  EXPECT_FALSE(sut.isLegalMove({0,1})); // hall to hall
  EXPECT_FALSE(sut.isLegalMove({10,9})); // hall to hall
  EXPECT_FALSE(sut.isLegalMove({2,4})); // burrow to burrow
  EXPECT_FALSE(sut.isLegalMove({2,9})); // to occupied burrow
  EXPECT_FALSE(sut.isLegalMove({4,9})); // to wrong burrow
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
  EXPECT_TRUE(sut.isLegalMove({2,3}));
  EXPECT_FALSE(sut.isLegalMove({3,2}));
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

TEST(Board, moves_from_a_hallway)
{
  Board sut;
  sut.put(1,'A');
  ASSERT_THAT(sut.moves(), ElementsAre(Move{1,2}));
}

TEST(Board, moves_from_a_burrow_when_home_is_taken)
{
  Board sut;
  sut.put(2,'B');
  sut.put(4,'C'); //To block b
  sut.put(6,'B'); //To block c
  ASSERT_THAT(sut.moves(), AllOf(Contains(Move{2,0})
				 ,Contains(Move{2,1})
				 ));
}


TEST(Board, example_first_step)
{
  EXPECT_EQ(Board(//01234567890
		  "#############"
		  "#..........D#"
		  "###A#B#C#.###"
		  "  #A#B#C#D#  "
		  "  #A#B#C#D#  "
		  "  #A#B#C#D#  "
		  "  #########  ").steps({10,8}), 3);
  EXPECT_EQ(Board(//01234567890
		  "#############"
		  "#..........D#"
		  "###A#B#C#.###"
		  "  #A#B#C#D#  "
		  "  #A#B#C#D#  "
		  "  #A#B#C#D#  "
		  "  #########  ").steps({8,9}), 3);

  EXPECT_EQ(Board(//01234567890
		  "#############"
		  "#.........D.#"
		  "###A#B#C#.###"
		  "  #A#B#C#D#  "
		  "  #A#B#C#D#  "
		  "  #A#B#C#D#  "
		  "  #########  ").steps({9,8}), 2);
}

TEST(Board, isLegalMove)
{
  EXPECT_FALSE(Board("#############"
		     "#.A.AA......#"
		     "###.#.#.#.###"
		     "  #.#.#.#.#  "
		     "  #.#.#.#.#  "
		     "  #B#.#.#.#  "
		     "  #########  "
		     ).isLegalMove({2,5}));
}

TEST(Board, isLegalMove_space)
{
  //                   01234567890  
  EXPECT_FALSE(Board("#############"
		     "#.....A.....#"
		     "###.#.#.#.###"
		     "  #.#.#.#.#  "
		     "  #.#.#.#.#  "
		     "  #B#.#.#.#  "
		     "  #########  "
		     ).isLegalMove({2,7}));
}

TEST(Board, isLegalMove_bug)
{
  //                   01234567890
  EXPECT_FALSE(Board("#############"
		     "#.....C.....#"
		     "###.#.#.#.###"
		     "  #.#.#.#.#  "
		     "  #B#.#B#D#  "
		     "  #A#D#C#A#  "
		     "  #########  "
		     ).isLegalMove({6,3}));
}

TEST(Board, quick_pass)
{
  //          01234567890
  Board sut("#############"
	    "#...........#"
	    "###.#.#.#.###"
	    "  #.#.#.#.#  "
	    "  #B#.#.#.#  "
	    "  #A#.#.#.#  "
	    "  #########  "
  //          01234567890
	    );
  EXPECT_THAT(sut.steps({2, 4}), Eq(9));
  EXPECT_TRUE(sut.isLegalMove({2, 4}));
}

TEST(Board, only_quick_pass_allowed_if_possible)
{
  //          01234567890
  Board sut("#############"
	    "#...........#"
	    "###.#.#.#.###"
	    "  #.#.#.#.#  "
	    "  #B#.#.#.#  "
	    "  #A#.#.#.#  "
	    "  #########  "
  //          01234567890
	    );
  EXPECT_THAT(sut.moves(), ElementsAre(Move(2,4)));
}


TEST(Board, move_that_does_not_move_is_illegal)
{
  Board sut;
  EXPECT_FALSE(sut.isLegalMove({1,1}));
}
