#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
using namespace std;

struct Coord{
  int south{0};
  int east{0};
  Coord operator+(Coord const &other ) const
  {
    Coord ret = *this;
    ret+=other;
    return ret;
  }
  void operator+=(Coord const &other )
  {
    south+=other.south;
    east+=other.east;
  }
  auto operator<=>(const Coord&) const = default;
  
};
ostream& operator<<(ostream &cout, Coord const &c)
{
  cout<<"{"<<c.south<<", "<<c.east<<"}";
  return cout;
}


enum class Di{e, se, sw, w, nw, ne};

Coord step(Coord start, Di d)
{
  switch(d)
    {
    case (Di::e):
      start.east+=2;
      return start;
    case (Di::w):
      start.east-=2;
      return start;
    case (Di::se):
      start.south+=1;
      start.east+=1;
      return start;
    case (Di::nw):
      start.south-=1;
      start.east-=1;
      return start;
    case (Di::sw):
      start.south+=1;
      start.east-=1;
      return start;
    case (Di::ne):
      start.south-=1;
      start.east+=1;
      return start;
      
    }
  assert(false);
}

using Nav = deque<Di>;

Coord step(Nav dir)
{
  Coord ret;
  for(Di d:dir)
    ret=step(ret, d);
  return ret;
}



