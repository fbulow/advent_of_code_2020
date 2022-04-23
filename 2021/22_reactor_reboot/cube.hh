#pragma once
#include "range.hh"
#include "point.hh"

struct Cube
{
  Range x;
  Range y;
  Range z;

  long long size() const;
  set<Cube> splitBy(Cube const & tr) const;
  set<Cube> punchOut(Cube const & tr) const;

  bool contains(Point const &p) const;
  Point centre() const;
};

bool operator<(Cube const &a, Cube const &b);
