#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <cassert>
using namespace std;

struct Inst{ //Instruction
  char cmd; //Command
  int arg;  //Arguments
};

istream& operator>>(istream& in, Inst &i)
{
  in>> i.cmd >> i.arg;

  if((i.cmd == 'L') or (i.cmd == 'R'))
     assert(i.arg%90==0);
  
  return in;
}

struct Instructions{
  vector<Inst> data;
  Instructions(string filename)
  {
    data.reserve(790);
    ifstream in(filename);
    assert(in.is_open());
    Inst latest;
    in>>latest;
    while(!in.eof())
      {
	data.push_back(latest);
	in>>latest;
      }
  }
  auto size() const
  {return data.size();}
  
};


struct Pos{
  int row;
  int column;

  
  bool operator==(Pos const & other) const
  {
    return (row==other.row) and (column==other.column);
  }
};

Pos step(Pos p, char direction, int distance)
{
  if('N'==direction)
    p.row-=distance;
  else if ('S'==direction)
    p.row+=distance;
  else if ('W'==direction)
    p.column-=distance;
  else if ('E'==direction)
    p.column+=distance;

  return p;
}


ostream& operator<<(ostream& cout, Pos const &p)
{
  cout<<"Pos{"<<p.row<<", "<<p.column<<"}";
  return cout;
}


class Ship
{
  int dir=0;
  void chDir(int deg)
  {
    dir+=deg/90;
    dir%=4;
  }

  Pos pos_{0,0};
  
public:
  Pos pos() const
  {
    return pos_;
  }
  
  char direction() const
  {
    switch(dir)
      {
      case 0:
	  return 'E';
      case 1:
	  return 'N';
      case 2:
	  return 'W';
      case 3:
	  return 'S';
      }
    assert(false);
    return ' ';
  }
  void apply(Inst const &inst)
  {
    switch(inst.cmd)
      {
      case 'L':
	chDir(inst.arg);
	return;
      case 'R':
	chDir(-inst.arg);
	return;
      }
    assert(false);
  }
};
