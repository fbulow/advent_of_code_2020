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

  Amphipod a{'.'};
  void pop(Column c)
  {
    a={'.'};
  }
  void put(Column c, Amphipod a)
  {
    this->a=a;
  }
  Amphipod getTop(Column c)
  {
    return a;
  }
  bool isBurrow(Column c) const;
};
