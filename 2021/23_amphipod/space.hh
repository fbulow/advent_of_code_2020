#pragma once
#include<vector>
#include "types.hh"
#include <cassert>
using namespace std;

class ConstFullDepth{
  uint depth_;
protected:
  uint fullDepth() const {return depth_;}
public:
  ConstFullDepth(uint depth)
    :depth_(depth)
  {}
};

class Space: ConstFullDepth, std::vector<Amphipod>
{
  Amphipod resident;
  bool isHallway_;
public:
  Space(uint depth=1, Amphipod resident='.')
    :ConstFullDepth(depth)
    ,std::vector<Amphipod>()
    ,resident(resident)
    ,isHallway_(depth==1)
  {
  }

  bool isHallway() const
  {return fullDepth()==1;}

  uint availableDepth() const
  {
    return fullDepth() - size();
  }

  bool isDone() const
  {
    if(resident=='.')
      return availableDepth()>0;
    else
      return (availableDepth()==0) and
	(getTop()==resident);
  }
  
  void pop()
  {
    pop_back();
  }
  void put(Amphipod a)
  {
    assert(availableDepth()>0);
    push_back(a);
  }
  Amphipod getTop()const
  {
    return empty()?'.':back();
  }
};
