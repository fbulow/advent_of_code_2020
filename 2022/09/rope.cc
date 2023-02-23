#include "rope.hh"

using namespace std;

bool isClose(Coord const &a, Coord const &b)
{
  return
    ( std::abs(a.row()-b.row())<=1 ) and
    ( std::abs(a.col()-b.col())<=1 ) ;
}

Coord Rope::step(char c)
{
  knots[0]=knots[0].step(c);
  for(size_t i=1; i<knots.size(); i++)
    if(not isClose(knots[i], knots[i-1]))
      knots[i] = knots[i].moveTowards(knots[i-1]);
  return knots.back();
}
