#pragma once
#include <set>
#include <vector>

#include "coord.hh"

using namespace std;


class Space : public set<Coord>
{
public:
  void drawLine(Coord const &from, Coord const &to);
  void drawSequence(vector<Coord> const &s);
private:
  void drawLine(int x0, int y0, int x1, int y1);
};

