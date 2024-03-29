#pragma once
#include <set>
#include <vector>
#include <string>

#include "coord.hh"

using namespace std;

class Done: std::exception{};


class Space : public set<Coord>
{
public:
  Space() = default;
  Space(string const & filename);
  Space(istream &in);

  void drawLine(Coord const &from, Coord const &to);
  void drawSequence(vector<Coord> const &s);
  void dropSnowflake(Coord);
  int lowestPoint() const;

protected:
  virtual bool hasHitTheFloor(Coord c) const;
  
private:
  void drawLine(int x0, int y0, int x1, int y1);
  void dropSnowflake_(Coord c);
  mutable int lowestPoint_{0};
};

void washLine(string &s);
void readInputFile(Space &, istream &in);

class SpaceB: public Space{
public:
    SpaceB(string const & filename)
      :Space(filename)
  {}
protected:
  bool hasHitTheFloor(Coord c) const override;
};
