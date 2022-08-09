#pragma once
#include<vector>
#include"move.hh"

class Board{
public:
  bool isDone() const{return true;}
  int score() const{return 0;}
  std::vector<Move> moves() const {return {};}
  Board apply(Move const & m) const {return {};}
};
