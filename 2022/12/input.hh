#pragma once
#include <set>
#include <string>
#include <vector>
#include "coord.hh"

using namespace std;


class Input: vector<string>
{
  vector<string> data;
  mutable set<Coord> allCoordinates_;
public:
  Input(vector<string> data);

  set<Coord> const & allCoordinates() const;
  bool isAdjacentToStepsValue(Coord c, Steps s) const //STARTED
  {
    
  }
  bool onBoard(Coord const & c);
  bool canMoveFromTo(Coord from, Coord to) const;
  vector<Coord> adjacent(Coord c);
  Coord find(char c) const;
};
