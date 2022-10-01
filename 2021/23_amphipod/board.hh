#pragma once
#include<vector>
#include"move.hh"
#include "result.hh"
#include "types.hh"
#include <array>
class Space: std::vector<Amphipod>
{
  uint depth_;
  Amphipod resident;
  bool isHallway_;
public:
  Space(uint depth=1, Amphipod resident='.')
    :depth_(depth)
    ,resident(resident)
    ,isHallway_(depth==1)
  {}

  bool isHallway() const
  {return isHallway_;}

  uint depth() const
  {
    return depth_-size();
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

inline bool swapOk(Amphipod const& a, Amphipod const& b)
{
  return (a!='.') xor (b!='.');
}

inline bool swapOk(Space const& a, Space const& b)
{
  return swapOk(a.getTop(), b.getTop());
}

class Board{
  Result score_{0};
  std::array<Space, 11> spaces;
public:
  bool isDone() const{return true;}
  Result score() const{return score_;}
  std::vector<Move> moves() const {
    std::vector<Move> ret;
    for(int i=0;i<11;i++)
      for(int j=0;j<i;j++)
	ret.emplace_back(Move(j,i));
    return ret;
  }
  virtual Result steps(Move) const {return 0;}
  Board apply(Move const & m) const
  {
    Board ret(*this);
    ret.put(m.to, getTop(m.from));
    ret.spaces[m.from].pop();
    
    ret.score_= score_ + steps(m);
    return ret;
  }

  void pop(Column c)
  {
    spaces[c].pop();
  }
  void put(Column c, Amphipod a)
  {
    spaces[c].put(a);
  }
  Amphipod getTop(Column c)const
  {
    return spaces[c].getTop();
  }
  bool isBurrow(Column c) const;
};
