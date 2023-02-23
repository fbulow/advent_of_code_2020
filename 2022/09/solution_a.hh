#pragma once

#include<set>
#include<sstream>
#include "rope.hh"
#include<array>

struct Solution
{
  Rope r;
  Solution(size_t knots=2)
    :r(knots)
  {}
  std::set<Coord> visited;
  int ans() const; 

  Coord step(char dir);
  Solution& operator<<(std::string const &s);
};

