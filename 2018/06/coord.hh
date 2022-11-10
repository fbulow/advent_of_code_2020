#include<tuple>
#include<vector>
#include<istream>
using namespace std;

class Coord : pair<int, int>
{
public:
  Coord(int row=0, int col=0);
  Coord(Coord const &c);

  int& row(){return first;}
  int& col(){return second;}
  int  row() const {return first;}
  int  col() const {return second;}
};
using Coords = vector<Coord>;

istream& operator>>(istream& in, Coord c);
istream& operator>>(istream& in, Coords v);
