#pragma once

#include<set>
#include<sstream>
#include "rope.hh"
#include<array>

struct Solution
{
  std::set<Coord> visited;
  int ans() const; 

  virtual Coord step(char dir) = 0;
  Solution& operator<<(std::string const &s);
};

struct SolutionA : Solution{
  Rope r;
  Coord step(char dir) override;
};
