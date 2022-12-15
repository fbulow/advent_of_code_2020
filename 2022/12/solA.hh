#pragma once

#include <vector>
#include <tuple>
#include <cassert>
#include <map>
#include <limits>
#include "coord.hh"
#include "int_types.hh"
#include "input.hh"

#include <AoC/getAllLines.hh>

using namespace std;






class Space{
public:
  Space(Coord topLeft, Coord bottomRight){assert(not "implemented");}
  bool inSpace(Coord c){assert(not "implemented");}
};


class StepCount;

Steps minAdjacent(Input const &, StepCount const &, Coord c);

class StepCount : public Space
{
  map<Coord, Steps> data_;
public:
  StepCount(Input)
    :Space(Coord(0,0), Coord(0,0))//TODO
  {
    //Same size as input but everything is set to -1;
    
  }//TODO

  static constexpr Steps unset = numeric_limits<Steps>::max();

  void  set(Steps, Coord){assert(not "implemented");}
  Steps get(Coord) const {assert(not "implemented");}
  bool isUnset(Coord) const {}//TODO
  void fillAllUnset(Input const &input, Steps current)//TODO
  {
    for (Coord c:allUnset())
      if(current == minAdjacent(c)+1)
	data_.at(c) = current;
  }
  vector<Coord> allUnset() const {assert(not "implemented");}
  
  Steps minAdjacent(Coord c)
  {
    Steps ret = StepCount::unset;
    for(Coord cc: c.adjacent())
      ret = min(ret, get(cc));
    return ret; 
  }
};

Coord findStart(Input const &data);
Coord findEnd  (Input const &data);

inline
int solA(Input data)
{
  Coord start = findStart(data);
  Coord stop  = findEnd  (data);

  StepCount sc(data);

  int steps = 0;
  sc.set(steps++, start);
  while(sc.isUnset(stop))
    sc.fillAllUnset(data, steps++);
      
  return sc.get(stop);
}
     
