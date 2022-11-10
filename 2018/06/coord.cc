#include "coord.hh"
#include<structured_input.hh>

Coord::Coord(int row, int col)
  :pair<int, int>(row,col)
{}

Coord::Coord(Coord const &c)
  :pair<int, int>(c)
{}


istream& operator>>(istream& in, Coord c)
{
  in>>c.row()>>", ">>c.col();
  return in;
}

istream& operator>>(istream& in, Coords v)
{
  Coord c;
  in>>v;
  while(not in.eof())
    {
      v.push_back(c);
      in>>v;
    }
  return in;
}

