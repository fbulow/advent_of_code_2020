#pragma once
#include<vector>
#include"move.hh"
#include "result.hh"
#include "types.hh"

class Board{
  Result score_{0};
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
    Board ret{};
    ret.score_= score_ + steps(m);
    return ret;
  }
  std::vector<Amphipod> burrow;
  void pop(Column c)
  {
    burrow.pop_back();
  }
  void put(Column c, Amphipod a)
  {
    burrow.push_back(a);
  }
  Amphipod getTop(Column c)const
  {
    if(burrow.empty())
      return '.';
    return *std::prev(burrow.cend());
  }
  bool isBurrow(Column c) const;
};
