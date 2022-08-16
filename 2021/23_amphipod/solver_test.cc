#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "solver.hh"
#include "board.hh"
using namespace testing;


TEST(DISABLED_Solver, return_smalles_number_of_steps)
{
  static int next_score{5};
  class :Board{
    int cost_of_next_move_{1};
  
  public:
    std::vector<Move> moves() const
    {
      return {Move{},Move{}};
    }
    bool isDone() const{return false;}
    int score() const{return next_score++;}

    Board apply(Move const & m) const
    {
      ::Board ret;
      assert(ret.isDone());
      return ret;
    }
  } b;

  auto ret = Solver(b);
  ASSERT_THAT(ret, Eq(true));

      
}

TEST(Solver, calls_apply_for_all_moves)
{
  static int apply_count{0};
  
  struct :Board{
    std::vector<Move> moves() const
    {
      return {Move{},Move{}};
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
    std::vector<Move> moves() const {return {Move{}};}
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
  ASSERT_THAT(Solver(b).value(), Eq(0));
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
    std::vector<Move> moves() const {return {Move{}};}
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

  ASSERT_THAT(Solver(b).value(), Eq(5));
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
  ASSERT_THAT(Solver(b).value(), testing::Eq(5));
}
