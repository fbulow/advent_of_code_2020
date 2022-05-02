#include "incl.hh"

bool hallway(Pos p)
{
  return p<'7';
}

array<char, 2> sideRooms(Amphipod a)
{
  switch(a)
    {
    case 'A':
      return {'7','b'};
    case 'B':
      return {'8','c'};
    case 'C':
      return {'9','d'};
    case 'D':
      return {'a','e'};
    }
  assert(false);
}

