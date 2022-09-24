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
public:
  Space(uint depth=0, Amphipod resident='.')
    :depth_(depth)
    ,resident(resident)
  {}

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
