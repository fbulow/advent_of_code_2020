#pragma once

#include <tuple>
#include <ostream>

class Coord : public std::pair<int,int>
{
public:
  Coord(auto ... arg)
  :std::pair<int,int>(arg...)
  {}
  
  int row() const;
  int col() const;
  Coord step(char c);
  
  Coord moveTowards(Coord const &other);
};



std::ostream& operator<<(std::ostream& out, Coord const &c);
