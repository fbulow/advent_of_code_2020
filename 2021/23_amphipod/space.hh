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
  Amphipod resident_;
  bool isHallway_;
public:
  Space(uint depth=1, Amphipod resident='.')
    :ConstFullDepth(depth)
    ,std::vector<Amphipod>()
    ,resident_(resident)
    ,isHallway_(depth==1)
  {
  }

  bool corridorIsBlocked() const;
  
  bool moveTo(Space & other)
  {
    if( not  canMoveTo(other))
      return false;
    else
      {
	other.put(getTop());
	pop();
	return true;
      }
  }
  
  bool canMoveTo(Space const & other) const
  {
    auto const a = getTop();

    if (not (isHallway() xor other.isHallway()))
      return false;
    if(a=='.')
      return false;
    else if(not other.onlyResidents())
      return false;
    else if(other.availableDepth()==0)
      return false;
    else if (other.resident() == '.')
      return not onlyResidents();
    else
      return other.resident()==a;
  }

  Amphipod resident() const {return resident_;}
  
  bool isHallway() const
  {return fullDepth()==1;}

  uint availableDepth() const
  {
    return fullDepth() - size();
  }

  bool isDone() const
  {
    if(resident_=='.')
      return availableDepth()>0;
    else
      return (availableDepth()==0) and
	onlyResidents();
  }

  bool onlyResidents() const
  {
    return all_of(cbegin(), cend(),
		  [this](Amphipod a){return a==resident_;});
  }
  
  void pop()
  {
    pop_back();
  }
  void put(Amphipod a)
  {
    if(a=='.') return; // DO nothing for if noting is put.
    assert(availableDepth()>0);
    push_back(a);
  }
  Amphipod getTop()const
  {
    return empty()?'.':back();
  }
  uint stepsToCorridor() const
  {
    if(isHallway())
      return 0;
    else
      return availableDepth();
  }

};
