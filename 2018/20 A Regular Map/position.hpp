#pragma once
#include<compare>

using namespace std;

struct Position{
  int row;
  int col;

  Position step(char direction) const;

  auto operator<=>(Position const & other) const
  {
    auto r = row <=> other.row;
    if (r==0)
      return col <=> other.col;
    else
      return r;
  }
  bool operator==(Position const & other) const = default;
    
  void operator=(Position const & other);
};

