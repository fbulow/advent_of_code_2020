#include "steps.hh"
#include "height.hh"
#include <limits>

void Steps::push(size_t row, size_t col, int value)
{
  if(row>=nRows) return;
  if(col>=nCols) return;
    
  board[row][col] = min(value, board[row][col]);    
}

int Steps::operator() (size_t row, size_t col) const
{
  return board[row][col];
}

void Steps::stepFrom(int const value)
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

bool Steps::climbOk(size_t fromRow, size_t fromCol,size_t toRow, size_t toCol) const
{
  if(fromRow>=nRows) return false;
  if(fromCol>=nCols) return false;
  if(toRow>=nRows) return false;
  if(toCol>=nCols) return false;
    
  auto after  = height(in[toRow][toCol]);
  auto before = height(in[fromRow][fromCol]);
  return (after-before)<=1;
}

Steps::Steps(Input &&in_)
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

bool Steps::done() const
{
  return ans() !=numeric_limits<int>::max();
}
