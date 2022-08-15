#pragma once
#include<vector>
#include"move.hh"

class Board{
  int score_{0};
public:
  bool isDone() const{return true;}
  int score() const{return score_;}
  std::vector<Move> moves() const {return {};}
  virtual int steps(Move) const {return 0;}
  Board apply(Move const & m) const
  {
    Board ret{};
    ret.score_+= steps(m);
    return ret;
  }
};
