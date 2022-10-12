#pragma once
#include<vector>
#include "types.hh"

using namespace std;

class Space: std::vector<Amphipod>
{
  uint depth_;
  Amphipod resident;
  bool isHallway_;
public:
  Space(uint depth=1, Amphipod resident='.')
    :std::vector<Amphipod>()
    ,depth_(depth)
    ,resident(resident)
    ,isHallway_(depth==1)
  {}

  bool isHallway() const
  {return isHallway_;}

  uint depth() const
  {
    return depth_-size();
  }

  bool isDone() const
  {
    if(depth()==0)
      return not isHallway();
    else
      return getTop()==resident;
  }
  
  void pop()
  {
    pop_back();
  }
  void put(Amphipod a)
  {
    if(a!=resident)
      push_back(a);
    else
      depth_--;
  }
  Amphipod getTop()const
  {
    return empty()?'.':back();
  }
};
