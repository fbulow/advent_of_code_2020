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

class StepCount;

class StepCount
{
  map<Coord, Steps> data_;
public:
  StepCount() = default;
  StepCount(Input)
  {
    //Same size as input but everything is set to -1;
    
  }//TODO

  static constexpr Steps unset = numeric_limits<Steps>::max();

  void  set(Coord c, Steps s)
  {
    data_[c]=s;
  }

  Steps get(Coord c) const
  {
    return data_.at(c);
  }

  bool isUnset(Coord c) const;

  void fillAllUnset(Input const &input, Steps current)//TODO
  {
    for(auto & c: input.allCoordinates())
      if(isUnset(c))
	if(input.isAdjacentTo(c, current-1))
	  data_.at(c) = current;
  }
  vector<Coord> allUnset() const {assert(not "implemented");}
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
  sc.set(start, steps++);
  while(sc.isUnset(stop))
    sc.fillAllUnset(data, steps++);
      
  return sc.get(stop);
}
     
