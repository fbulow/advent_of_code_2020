#include<gtest/gtest.h>
#include<vector>
using namespace std;
//#############
//#01 2 3 4 56#
//###7#8#9#a###
//  #b#c#d#e#
//  #########


using Score = unsigned int;

struct Move {};

class Board{
public:
  enum class Status {Finished, Failed, InProgress};
  virtual Status status() const
  {
    if(done())
      return Status::Finished;
    else if(moves().size()>0)
      return Status::InProgress;
    else
      return Status::Failed;
  }
  
  virtual Score score() const {return {};}
  virtual vector<Move> moves() const {return {};}
  virtual bool done() const
    {
      return false;
    }
};


Score solutionA(Board const &board, Score bestScore = 10)
{
  switch(board.status())
    {
    case Board::Status::Failed:
      return bestScore;
    case Board::Status::Finished:
      return min(board.score(), bestScore);
    }
}

TEST(soution_a, return_previous_best)
{
  struct : Board
  {
    Status status() const override
    {return Status::Finished;}
    
    Score score() const override
    {
      return 20;
    }
    
  } board;

  EXPECT_EQ(10, 
	    solutionA(board, Score(10)));
    
}

TEST(soution_a, return_new_score)
{
  struct : Board
  {
    Status status() const override
    {return Status::Finished;}
    
    Score score() const override
    {
      return 5;
    }
    
  } board;

  EXPECT_EQ(5, 
	    solutionA(board, Score(10)));
    
}

TEST(soution_a, return_previous_best_if_failed)
{
  struct : Board
  {
    Status status() const override
    {return Status::Failed;}
    
    Score score() const override
    {
      return 5;
    }
    
  } board;

  EXPECT_EQ(10, 
	    solutionA(board, Score(10)));
    
}

TEST(soution_a, status_InProgress_when_there_are_moves)
{
  struct : Board
  {
    // Status status() const override
    // {return Status::InProgress;}
    
    vector<Move> moves() const override
    {
      return {{}};//contains one
    }
    
  } sut;

  EXPECT_EQ(Board::Status::InProgress,
	    sut.status());
}

TEST(soution_a, failed_when_not_done_and_no_moves)
{
  struct : Board
  {
    vector<Move> moves() const override
    {
      return {};//contains one
    }

    bool done() const override
    {
      return false;
    }
    
  } sut;

  EXPECT_EQ(Board::Status::Failed,
	    sut.status());
}

TEST(soution_a, done_when_done)
{
  struct : Board
  {
    bool done() const override
    {
      return true;
    }
    
  } sut;

  EXPECT_EQ(Board::Status::Finished,
	    sut.status());
}
