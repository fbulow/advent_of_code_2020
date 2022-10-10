#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "solver.hh"
#include "board.hh"
#include "move.hh"
using namespace testing;

TEST(Solver, return_smalles_number_of_steps)
{
  class OneMoveBoard{
  public:
    bool isDone_ = {false};
    int score_{0};
    bool isDone() const {return isDone_;}
    int score() const {return score_;}
    std::vector<int> moves() const
    {
      return {1,2,3,4};
    }
  
    OneMoveBoard apply(int a) const
    {
      return OneMoveBoard{true, a};
    }
  } b;

  auto ret = Solver(b);
  ASSERT_THAT(ret, Eq(1));

      
}

TEST(Solver, calls_apply_for_all_moves)
{
  static std::set<int> seen{};

  class OneMoveBoard{
  public:
    
    bool isDone_ = {false};
    bool isDone() const {return isDone_;}
    int score() const {return {};}
    std::vector<int> moves() const
    {
      return {1,2,3,4};
    }
  
    OneMoveBoard apply(int a) const
    {
      seen.insert(a);
      return OneMoveBoard{true};
    }
  } b;

  Solver(b);
  ASSERT_THAT(seen.size(), Eq(4));
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


TEST(Solver, do_not_call_apply_if_done)
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
  ASSERT_THAT(count, Eq(0));
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
    std::vector<Move> moves() const {return {};}
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
