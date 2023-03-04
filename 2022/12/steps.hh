#pragma once
#include <vector>
#include "read_input.hh"
using namespace std;

class Steps
{
public:
  Input in;
  vector<vector<int>> board;
  size_t nRows;
  size_t nCols;

  size_t endRow;
  size_t endCol;
  
  Steps(Input &&in_);

  int operator() (size_t row, size_t col) const;

  void push(size_t row, size_t col, int value);

  auto ans() const
  {
    return board[endRow][endCol];
  }

  bool done() const;
  
  void stepFrom(int const value);
  bool climbOk(size_t fromRow, size_t fromCol,size_t toRow, size_t toCol) const;
};
