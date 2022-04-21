#pragma once
#include "range.hh"

struct Cube
{
  Range x;
  Range y;
  Range z;

  long size() const;
  set<Cube> splitBy(Cube const & tr)
  {
    set<Cube> ret;
    return ret;
  }

};
