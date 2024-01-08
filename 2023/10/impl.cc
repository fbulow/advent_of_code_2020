#include <algorithm>
#include <fstream>
#include <initializer_list>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include <vector>
using namespace std;

using Tile = char;
using Dir  = char;

class Pos:tuple<size_t, size_t>
{
public:
  Pos(size_t row, size_t col)
    :tuple<size_t, size_t>(row, col)
  {}
  auto row() const
  {
    return get<0>(*this);
  }
  auto col() const
  {
    return get<1>(*this);
  }
  Pos move(Dir d) const
  {
    switch(d)
      {
      case 'N':
	return {row()-1, col()};
      case 'S':
	return {row()+1, col()};
      case 'E':
	return {row(), col()+1};
      case 'W':
	return {row(), col()-1};
      }
    assert(false);
  }
  friend bool operator==(Pos const &,Pos const &);
  friend bool operator<(Pos const &,Pos const &);
};

bool operator==(Pos const &,Pos const &) = default;
bool operator<(Pos const &,Pos const &) = default;


class Map;
Dir initialDir(Map const &m, Pos const & initialPos);

struct Map : vector<string>
{
  Map() = default;
  Map(initializer_list<string> x)
    :vector<string>(x)
  {}
  Map(istream &&in)
  {
    string row;
    while(getline(in,row))
      push_back(row);
  }

  Tile& at(Pos const &p) {return (*this)[p.row()][p.col()];}
  Tile const & at(Pos const &p) const {return (*this)[p.row()][p.col()];}
};

Pos findS(Map const &m)
{
  for(size_t row=0; row< m.size(); row++)
    {
      auto c = m[row].find('S');
      if(c!=string::npos)
	return Pos(row, c);
    }
  assert(false);
}
  
Dir nextDir(Dir d)
{
  switch(d)
    {
    case 'N': return 'E';
    case 'E': return 'S';
    case 'S': return 'W';
    case 'W': return 'N';
    default : assert(false);
    }
}


auto furthestDistance(auto x)
{
  assert(x%2==0);
  return x/2;
}

bool isValidMove(Map const &m, Pos p, Dir d)
{
  p = p.move(d);
  if(p.col()<0) return false;
  if(p.row()<0) return false;
  if(p.row()>=m.size()) return false;
  if(p.col()>=m[p.row()].size()) return false;
  auto dest = m.at(p);

  switch(dest)
    {
    case '.': return false;
    case 'S': return true;
    case '-': return (d=='E') || (d=='W');
    case '|': return (d=='N') || (d=='S');
    case 'L': return (d=='S') || (d=='W');
    case 'J': return (d=='S') || (d=='E');
    case '7': return (d=='N') || (d=='E');
    case 'F': return (d=='N') || (d=='W');
    }
  assert(false);
}

Dir initialDir(Map const &m, Pos const & initialPos)
{
  Dir ret = 'N';
  while( ! isValidMove(m, initialPos, ret))
    ret = nextDir(ret);
  return ret;
}
