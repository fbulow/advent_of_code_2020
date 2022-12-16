#include "solA.hh"

Coord findStart(Input const &data)
{
  return data.find('S');
}

Coord findEnd  (Input const &data)
{
  return data.find('E');
}

bool StepCount::isUnset(Coord c) const
{
  return data_.find(c)==data_.end();
}
