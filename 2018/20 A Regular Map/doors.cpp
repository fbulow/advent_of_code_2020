#include "doors.hpp"
#include "strong_type.hpp"
#include "transverse.hpp"
Door::Door(Position const & a, Position const &b)
  :a(min(a,b))
  ,b(max(a,b))
{
  assert(a!=b);
}

bool Door::has(Position const &p) const
{
  return (a==p) or (b==p);
}


Position Door::other(Position const &p) const 
{
  if(a==p)
    return b;
  else
    {
      assert (b==p);
      return a;
    }
}

ostream& operator<<(ostream& out, Doors const &d)
{
  return out;
}

Doors::Doors(string s)
{
  istringstream in(s);
  transverse_ignore_branching(in,
                              Trail(*this));
}
