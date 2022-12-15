#include "solA.hh"

Coord findStart(Input const &data)
{
  return data.find('S');
}

Coord findEnd  (Input const &data)
{
  return data.find('E');
}
