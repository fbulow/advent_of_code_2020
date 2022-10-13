#pragma once
#include"move.hh"
#include "result.hh"
#include "types.hh"
#include <array>
#include "space.hh"

unsigned int costPerStep(Amphipod a);


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

  vector<Move> moves() const;
  
  Result steps(Move const&m) const;

  bool isLegalMove(Move const & m) const;
  
  Board apply(Move const & m) const
  {
    assert(isLegalMove(m));
    Board ret(*this);
    ret.put(m.to, getTop(m.from));
    ret.spaces[m.from].pop();
    
    ret.score_= score_ + steps(m)*costPerStep(getTop(m.from));
    return ret;
  }

  void pop(Column c);
  void put(Column c, Amphipod a);
  Amphipod getTop(Column c) const;
  bool isBurrow(Column c) const;
};

inline
ostream& operator<<(ostream& out, Board b)
{
  bool done=false;
  out<<"01234567890"<<endl;
  while(not done)
    {
      done = true;
      for(int i =0;i<11;i++)
	{
	  auto c = b.getTop(i);
	  out<<c;
	  if(c!='.')
	    {
	      b.pop(i);
	      done=false;
	    }
	}
      out<<endl;
    }
    return out;
}
