#pragma once
#include <vector>
#include <string>
#include "coord.hh"

using namespace std;


class Input: vector<string>
{
  vector<string> data;

public:
  Input(vector<string> data);

  vector<Coord> allCoordinates() const
  {
    vector<Coord> ret;
    ret.resize(data.size() * data[0].size());
    return ret;
  }
  bool isAdjacentTo(Coord c, Steps s) const {assert(not "implemented");}
  bool onBoard(Coord const & c);
  bool canMoveFromTo(Coord from, Coord to) const;
  vector<Coord> adjacent(Coord c);
  Coord find(char c) const;
};
