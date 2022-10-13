#pragma once
#include"move.hh"
#include "result.hh"
#include "types.hh"
#include <array>
#include "space.hh"

inline unsigned int costPerStep(Amphipod a)
{
  switch(a)
    {
    case 'A':
      return 1;
    case 'B':
      return 10;
    case 'C':
      return 100;
    case 'D':
      return 1000;
    }
  assert(false);
}

inline bool swapOk(Space const& a, Space const& b)
{
  return a.canMoveTo(b) or b.canMoveTo(a);
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

  unsigned int burrow(Amphipod a) const;

  static Board failed();

  bool isDone() const;
  Result score() const{return score_;}

  bool swapOk(Move const &m) const
  {
    return ::swapOk(spaces[m.from], spaces[m.to]);
  }
  
  vector<Move> moves() const;
  
  Result steps(Move const&m) const;
  
  Board apply(Move const & m) const
  {

    if (not spaces[m.from].canMoveTo(spaces[m.to]))
      return Board::failed();
    Board ret(*this);
    ret.put(m.to, getTop(m.from));
    ret.spaces[m.from].pop();
    
    ret.score_= score_ + steps(m)*costPerStep(getTop(m.from));
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

