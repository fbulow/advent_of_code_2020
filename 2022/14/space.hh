#pragma once
#include <set>
#include "coord.hh"

class Space : public set<Coord>
{
private:
  void drawLine(int x0, int y0, int x1, int y1);
public:
  void drawLine(Coord const &from, Coord const &to);
};

