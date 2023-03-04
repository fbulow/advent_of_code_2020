#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include "read_input.hh"
#include <algorithm>

using namespace testing;
using namespace std;

int height(char c)
{
  switch(c)
    {
    case 'S':
      return 'a';
    case 'E':
      return 'z';
    default:
      return c;
    }
}

class Steps
{
public:
  Input in;
  vector<vector<int>> board;
  size_t nRows;
  size_t nCols;

  size_t endRow;
  size_t endCol;
  
  Steps(Input &&in_)
    :in(move(in_))
    ,nRows(in.size())
    ,nCols(in[0].size())
  {
    board.reserve(nRows);
    for(auto x: in)
      board.emplace_back(vector<int>(nCols, numeric_limits<int>::max()));

    for(auto row=0;row<nRows;row++)
      for(auto col=0;col<nCols;col++)
	if(in[row][col]=='S')
	  board[row][col]=0;
	else if(in[row][col]=='E')
	  {
	    endRow = row;
	    endCol = col;
	  }
  }

  auto operator() (size_t row, size_t col) const
  {
    return board[row][col];
  }

  void push(size_t row, size_t col, int value)
  {
    if(row>=nRows) return;
    if(col>=nCols) return;
    
    board[row][col] = min(value, board[row][col]);    
  }

  auto ans() const
  {
    return board[endRow][endCol];
  }

  bool done() const
  {
    return ans() !=numeric_limits<int>::max();
  }

  
  void stepFrom(int const value)
  {
    for(auto row=0;row<nRows;row++)
      for(auto col=0;col<nCols;col++)
	if(board[row][col]==value)
	  {
	    auto p = [this, row, col, value]
	      (int drow, int dcol)
	    {
	      if(climbOk(row, col, row+drow, col+dcol))
		push(row+drow, col+dcol, value+1);
	    };
	    p(+1, 0);
	    p(-1, 0);
	    p(0, +1);
	    p(0, -1);
	  }
  }
  
  bool climbOk(size_t fromRow, size_t fromCol,size_t toRow, size_t toCol) const
  {
    if(fromRow>=nRows) return false;
    if(fromCol>=nCols) return false;
    if(toRow>=nRows) return false;
    if(toCol>=nCols) return false;
    
    auto after  = height(in[toRow][toCol]);
    auto before = height(in[fromRow][fromCol]);
    return (after-before)<=1;
  }
};

TEST(Steps, climbOk)
{
  ifstream in(EXAMPLE);
  auto sut = Steps(readInput(in));

  EXPECT_TRUE(sut.climbOk(0,0,1,0));
  EXPECT_FALSE(sut.climbOk(0,2,0,3));

}

TEST(Steps, ctor)
{
  ifstream in(EXAMPLE);
  auto sut = Steps(readInput(in));
  EXPECT_THAT(sut(0,0), Eq(0));//Start at S
  sut.push(1,0,1);
  EXPECT_THAT(sut(1,0), Eq(1));

  sut.stepFrom(1);
  
  EXPECT_THAT(sut(1,1), Eq(2));

  sut.push(0, 2, 5);
  sut.stepFrom(5);
  EXPECT_THAT(sut(0,3), Ne(6));

  EXPECT_FALSE(sut.done());
  sut.push(5,2,10);
  EXPECT_FALSE(sut.done());
  
}


TEST(readInput, example)
{
  ifstream in(EXAMPLE);
  auto sut = readInput(in);

  EXPECT_THAT(sut[0], Eq("Sabqponm"));
  EXPECT_THAT(sut[1], Eq("abcryxxl"));
  EXPECT_THAT(sut[2], Eq("accszExk"));
  EXPECT_THAT(sut[3], Eq("acctuvwj"));
  EXPECT_THAT(sut[4], Eq("abdefghi"));
  EXPECT_THAT(sut.size(), Eq(5));
}
