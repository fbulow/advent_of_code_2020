#pragma once
#include"move.hh"
#include "result.hh"
#include "types.hh"
#include <array>
#include "space.hh"

inline bool swapOk(Amphipod const& a, Amphipod const& b)
{
  return (a!='.') xor (b!='.');
}

inline bool swapOk(Space const& a, Space const& b)
{
  return
    (a.isHallway() xor b.isHallway())
    && swapOk(a.getTop(), b.getTop());
}

class Board{
  Result score_{0};
  std::array<Space, 11> spaces;
  bool isValidVisual(string_view vi) const;
  void readColumn(std::string_view vi, int col)
  {
    size_t offset = col-2;

    put(col, vi[68+offset]);
    put(col, vi[55+offset]);
    put(col, vi[42+offset]);
    put(col, vi[29+offset]);
  }
public:
  Board(std::string_view visual);
  Board(int depth=4);
  static Board failed();

  bool isDone() const;
  Result score() const{return score_;}

  std::vector<Move> moves() const
  {
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
