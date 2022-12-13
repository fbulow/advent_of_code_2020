#pragma once
#include <vector>
#include <string>
#include "coord.hh"

using namespace std;


class Input: vector<string>
{
  vector<string> data;

public:
  Input(vector<string> data)
    :vector<string>(move(data))
  {}

  bool isValidStep(Coord from, Coord to) const {assert(not "implemented");}
  vector<Coord> adjacent(Coord c)
  {
    assert(not "implemented");
    //Returns all coordinates that can be reached from c
    vector<Coord> ret;
    for(Coord cc : c.adjacent())
      if(isValidStep(c, cc))
	ret.push_back(cc);
    return ret;
  }
};
