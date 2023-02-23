#pragma once
#include"coord.hh"
#include<vector>
class Rope{
  std::vector<Coord> knots;
public:
  Rope(size_t numberOfKnots=2)
    :knots(numberOfKnots)
  {}
  Coord step(char c);
};
