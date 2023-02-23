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
    head = head.step(c);
    if(not isClose(head, tail))
      tail = tail.moveTowards( head );
    return tail;
  }
