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

  bool onBoard(Coord const & c)
  {
    if(c.row() < data.size()) //Also false if row() is negative due to signed/unsigned arithmetics!
      if (c.col() < data[c.row()].size())
	return true;
    return false;
  }
  
  bool canMoveFromTo(Coord from, Coord to) const;

  vector<Coord> adjacent(Coord c) //STARTED
  {
    vector<Coord> ret;
    for(Coord cc : c.adjacent())
      if(onBoard(cc))
	//if(  ... the step is not to high 
	ret.push_back(cc);
      
    // assert(not "implemented");
    // //Returns all coordinates that can be reached from c
    // vector<Coord> ret;
    // for(Coord cc : c.adjacent())
    //   if(canMoveFromTo(c, cc))
    // 	ret.push_back(cc);
    return ret;
  }
};
