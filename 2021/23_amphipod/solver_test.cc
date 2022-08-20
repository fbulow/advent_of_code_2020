#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "solver.hh"
#include "board.hh"
#include "move.hh"
using namespace testing;

TEST(Solver, return_smalles_number_of_steps)
{
  static int next_steps{0};
  struct :Board{
    std::vector<Move> moves() const
    {
      auto m = A::Move();
      return {m,m,m};
    }
    bool isDone() const{return false;}
    Result steps(Move) const override {
      switch(next_steps++)
	{
	case 0:return 6;
	case 1:return 5;
	case 2:return 7;
	default:
	  return 10;
	}
    }

  } b;

  auto ret = Solver(b);
  ASSERT_THAT(ret, Eq(5));

      
}

TEST(Solver, calls_apply_for_all_moves)
{
  static int apply_count{0};
  
  struct :Board{
    std::vector<Move> moves() const
    {
      auto m = A::Move();
      return {m,m};
    }
    bool isDone() const{return false;}
    Board apply(Move const & m) const
    {
      apply_count++;
      ::Board ret;
      assert(ret.isDone());
      return ret;
    }
  } b;
  Solver(b);
  ASSERT_THAT(apply_count, Eq(2));
}

TEST(Solver, recursive_call_on_return_value_of_apply)
{
  struct :Board{
    std::vector<Move> moves() const {return {A::Move()};}
    Board apply(Move const & m) const{
      ::Board ret;
      assert(ret.isDone());
      assert(ret.score() == 0 );

      return ret;
    }
    int score() const{
      return 5; // not zero
    }

  } b;
  ASSERT_THAT(Solver(b), Eq(0));
}

TEST(Solver, do_not_call_apply_if_moves_empty)
{
  static int count{0};
  struct :Board{
    bool isDone() const {return true;}
    std::vector<Move> moves() const {return {};}
    Board apply(Move const & m) const{
      count++;
      return ::Board::apply(m);
    }
  }b;

  Solver(b);
  ASSERT_THAT(count, Eq(0));
}


TEST(Solver, call_apply_if_moves_not_empty)
{
  static int count{0};
  struct :Board{
    bool isDone() const {return true;}
    std::vector<Move> moves() const {return {A::Move()};}
    Board apply(Move const & m) const{
      count++;
      return ::Board::apply(m);
    }
  }b;

  Solver(b);
  ASSERT_THAT(count, Eq(1));
}

TEST(Solver, return_score_if_no_moves_and_isdone)
{
  struct :Board{
    bool isDone() const {return true;}
    std::vector<Move> moves() const {return{};}
    int score() const{return 5;}
  }b;

  ASSERT_THAT(Solver(b), Eq(5));
}

TEST(Solver, return_nothing_if_failed)
{
  struct :Board{
    bool isDone() const {return false;}
  }b;
  ASSERT_FALSE(Solver(b));
}

TEST(Solver, return_current_score_if_done)
{
  struct :Board{
    bool isDone() const {return true;}
    int score() const { return 5; }
  }b;
  ASSERT_THAT(Solver(b), testing::Eq(5));
}
