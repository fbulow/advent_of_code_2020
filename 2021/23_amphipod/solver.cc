#include "solver.hh"
#include<cassert>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<optional>

class Move{

};

class Board{
public:
  bool isDone() const{return true;}
  int score() const{return 0;}
  std::vector<Move> moves() const {return {};}
  Board apply(Move const & m) const {return {};}
};

template<class BOARD>
std::optional<int> Solver(BOARD const &b)
{
  auto m = b.moves();
  if(m.empty())
    {
      if (b.isDone())
	return {b.score()};
      else
	return {};
    }
  else
    {
      return Solver(b.apply({}));
    }
}

using namespace testing;

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



