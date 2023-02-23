#include "coord.hh"
#include <cassert>

int Coord::row() const {return std::get<0>(*this);}
int Coord::col() const {return std::get<1>(*this);}
Coord Coord::step(char c)
{
  switch(c)
    {
    case 'R': return {row()+0, col()+1};
    case 'L': return {row()+0, col()-1};
    case 'U': return {row()-1, col()+0};
    case 'D': return {row()+1, col()+0};
    }
  assert(false);
}

std::ostream& operator<<(std::ostream& out, Coord const &c)
{
  return out<<"("<<c.row()<<", "<<c.col()<<")";
}




Coord Coord::moveTowards(Coord const &other)
{
  Coord ret(*this);
  
  if(other.row()>row())
    get<0>(ret)+=1;
  else if(other.row()<row())
    get<0>(ret)-=1;

  if(other.col()>col())
    get<1>(ret)+=1;
  else if(other.col()<col())
    get<1>(ret)-=1;

  return ret;
}
  
