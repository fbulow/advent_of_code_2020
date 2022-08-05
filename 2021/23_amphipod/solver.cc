#include "solver.hh"
#include<cassert>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<optional>

class Board{
public:
  enum class Status {Done, Failed};
  virtual Status status() const = 0;
  virtual int score() const {return 0;}
};

std::optional<int> Solver(Board const &b)
{
  switch(b.status())
    {
    case Board::Status::Done:
      return {b.score()};
    case Board::Status::Failed:
      return {};
    }
  assert(false);
}

TEST(Solver, return_current_score_if_done)
{
  struct :Board{
    Status status() const override
    {
      return Status::Done;
    }
    int score() const {return 5;}
  } b;
  
  ASSERT_THAT(Solver(b).value(), testing::Eq(5));
}

TEST(Solver, return_nothing_if_failed)
{
  struct :Board{
    Status status() const override
    {
      return Status::Failed;
    }
  } b;
  ASSERT_FALSE(Solver(b));
}


TEST(Solver, return_score_if_done)
{
  struct :Board{
    Status status() const override
    {
      return Status::Done;
    }
  } b;
  ASSERT_TRUE(Solver(b));
}

