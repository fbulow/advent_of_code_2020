#pragma once
#include "range.hh"

struct Cube
{
  Range x;
  Range y;
  Range z;

  long size() const;
  set<Cube> splitBy(Cube const & tr) const;

};

bool operator<(Cube const &a, Cube const &b);
