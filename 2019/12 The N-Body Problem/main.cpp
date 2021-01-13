#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
#include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
#include <functional>
#include <boost/algorithm/string.hpp> 
#include <boost/algorithm/string/join.hpp>
#include "intcode.hpp"

using Coord = array<int,3>;

struct Moon{
  Coord pos{0,0,0};
  Coord vel{0,0,0};
};

istream& operator>>(istream& in, Moon &m)
{
  string line;
  getline(in, line);
  auto e= line.end();
  auto s = find(line.begin(), line.end(), '=');
  istringstream({next(s),e}) >> m.pos[0];

  s = find(next(s), line.end(), '=');
  istringstream({next(s),e}) >> m.pos[1];

  s = find(next(s), line.end(), '=');
  istringstream({next(s),e}) >> m.pos[2];

  
  return in;
}

ostream& operator<<(ostream& out, Coord const &m)
{
  out<<m[0]<<", "<<m[1]<< ", "<<m[2];
  return out;
}

ostream& operator<<(ostream& out, Moon const &m)
{
  out << m.pos << " | "<< m.vel;
  return out;
}

struct Jupiter
{
  vector<Moon> moons;
  Jupiter(string filename)
  {
    moons.reserve(4);
    ifstream in(filename);
    assert(in.is_open());
    Moon m;
    string line;
    for(auto j=0;j<4;j++)
      {
        getline(in, line);
        istringstream(line) >> m;
        moons.push_back(m);
      }
  }

  void updatePosition()
  {
    for(auto &m:moons)
      for(int i=0;i<3;i++)
        m.pos[i]+=m.vel[i];
  }
  
  void updateVelocity()
  {
    for(auto &m:moons)
      for(int i=0;i<3;i++)
        {
          m.vel[i] =
            count_if(moons.begin(),
                     moons.end(),
                     [m, i](auto const &x)
                     {
                       return x.pos[i] > m.pos[i];
                     })
            -
            count_if(moons.begin(),
                     moons.end(),
                     [m, i](auto const &x)
                     {
                       return x.pos[i] < m.pos[i];
                     });
        }
  }
  
  void step()
  {
    
  }
  
};


