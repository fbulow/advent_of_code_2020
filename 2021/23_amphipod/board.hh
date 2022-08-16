#pragma once
#include<vector>
#include"move.hh"
#include "result.hh"

class Board{
  Result score_{0};
public:
  bool isDone() const{return true;}
  Result score() const{return score_;}
  std::vector<Move> moves() const {return {};}
  virtual Result steps(Move) const {return 0;}
  Board apply(Move const & m) const
  {
    Board ret{};
    ret.score_+= steps(m);
    return ret;
  }
};
