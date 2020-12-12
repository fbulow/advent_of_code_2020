#include <cmath>
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

  void rotateRight(int angle)
  {
    if(angle<0)
      angle+=360*(1-angle/360);
    assert(angle>0);
    angle/=90;
    for(auto i=0;i<angle;i++)
      rotateRight90();
  }
  
  void rotateRight90()
  {
    swap(row, column);
    column*=-1;
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
    while(dir<0)
      dir+=4;
    dir%=4;
  }

  Pos pos_{0,0};
  
public:
  void rotateRight(int angle)
  {
    pos_.rotateRight(angle);
  }
  
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
      case 'N':
      case 'S':
      case 'E':
      case 'W':
	pos_ = step(pos(), inst.cmd, inst.arg);
	return;
      case 'F':
	pos_ = step(pos(),
		    direction(),
		    inst.arg);
	return;
      }
    assert(false);
  }
};

char oppositeDirection(char dir)
{
  switch(dir)
    {
    case 'E':
      return 'W';
    case 'W':
      return 'E';
    case 'N':
      return 'S';
    case 'S':
      return 'N';
    }
  assert(false);
  return ' ';
}



struct ShipAndWaypoint{
  Ship s;
  Ship w;
  ShipAndWaypoint()
  {
    w.apply({'E', 10});
    w.apply({'N', 1 });
  }
  
  void apply(Inst const &inst)
  {
    switch(inst.cmd)
      {
      case 'F':
	s.apply({'S', inst.arg*w.pos().row});
	s.apply({'E', inst.arg*w.pos().column});
	return;
      case 'N':
      case 'S':
      case 'E':
      case 'W':
	w.apply(inst);
	return;
      case 'L':
	apply({'R', -inst.arg});
	return;
      case 'R':
	w.rotateRight(inst.arg);
	return;
      }
    assert(false);
  }
};



int manhattanMetric(Pos const &p)
{
  return abs(p.row)+abs(p.column);
}

int solveA(string const &filename)
{
  Ship s;
  for(auto x:Instructions(filename).data)
    s.apply(x);
  return manhattanMetric(s.pos());
}

int solveB(string const &filename)
{
  ShipAndWaypoint s;
  for(auto x:Instructions(filename).data)
    s.apply(x);
  return manhattanMetric(s.s.pos());
}
