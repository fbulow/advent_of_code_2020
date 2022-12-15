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
    :data(move(data))
  {}

  bool canMoveFromTo(Coord from, Coord to) const
  {

    auto heightIncrease =
      data[to.row()  ][to.col()  ]
      -
      data[from.row()][from.col()]
      ;

    return heightIncrease <=1;
  }

  vector<Coord> adjacent(Coord c)
  {
    assert(not "implemented");
    //Returns all coordinates that can be reached from c
    vector<Coord> ret;
    for(Coord cc : c.adjacent())
      if(canMoveFromTo(c, cc))
	ret.push_back(cc);
    return ret;
  }
};
