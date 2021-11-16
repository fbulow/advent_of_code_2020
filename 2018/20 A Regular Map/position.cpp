#include "position.hpp"
#include <cassert>
Position Position::step(char direction) const
{
  switch(direction)
  {
  case 'N':
    return {row-1, col};
  case 'S':
    return {row+1, col};
  case 'E':
    return {row,   col+1};
  case 'W':
    return {row,   col-1};
  }
  assert(false);  
}


void Position::operator=(Position const & other)
{
  row = other.row;
  col = other.col;
}

ostream& operator<<(ostream& out, Position const &p)
  {
    out<<"Pos{"<<p.row<<","<<p.col<<"}";
    return out;
  }
