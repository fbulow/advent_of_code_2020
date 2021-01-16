#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <ranges>
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

int absoluteSum(Coord const &c)
{
  return abs(c[0]) +abs(c[1]) +abs(c[2]);
}


struct Moon{
  Coord pos{0,0,0};
  Coord vel{0,0,0};

  int energy() const
  {
    return absoluteSum(pos)*absoluteSum(vel);
  }
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


  using DimState = array<int, 8>;
  DimState state(int i)
  {
    return {
      moons[0].pos[ i ] , moons[0].vel[ i ] ,
      moons[1].pos[ i ] , moons[1].vel[ i ] ,
      moons[2].pos[ i ] , moons[2].vel[ i ] ,
      moons[3].pos[ i ] , moons[3].vel[ i ] };
      
  }
  
  int energy()
  {
    return accumulate(moons.begin(),
                      moons.end(),
                      0,
                      [](int s, Moon const &m)
                      {return s+m.energy();});
                      
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
          m.vel[i]+=
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
  
  Jupiter& step(unsigned int n = 1)
  {
    while(n-->0)
      {
        updateVelocity();
        updatePosition();
      }
    return *this;
  }
  
};


int solutionA(string filename)
{
  return Jupiter(filename).step(1000).energy();
}


using State  =  Jupiter::DimState;
bool operator<( State const &a, State const &b)
{
  for(int i = 0; i < a.size();i++)
    if(a[i] != b[i])
      return a[i]<b[i];
  return false;
}

class CycleFinder
{
public:
  using I = unsigned long long int;
private:
  map<State, I> data;
  I step = 0;
public:
  bool done{false};
public:
  I beginning;
  I ending;
  I cycle()
  {return ending -beginning;}
  
  void push(State state)
  {
    if (done) return ;
    auto& p = data[state];
    if(p==0)
      p=step++;
    else
      {
        done=true;
        beginning = p;
        ending = step;
      }
  }
};

unsigned long long int smallestNumberThatIsDivisiblebyAllOther(std::vector<CycleFinder::I> data)
{
  unsigned long long int ret = 1;
  int factor=2;
  while(find_if(data.begin(), data.end(), [](auto x){return x!=1;}) != data.end())
    {
      while(any_of(data.begin(), data.end(),
                     [factor](auto &x)
                     {
                       return (x%factor==0);
                     }))
      {
        for(auto &x:data)
          if(x%factor==0)
            x/=factor;
        ret*=factor;
      }
      
      factor++;
    }
  return ret;
}


unsigned long long int solutionB(Jupiter &&j)
{
  CycleFinder x, y, z;
  while( not (x.done and y.done and z.done) )
    {
      x.push(j.state(0));
      y.push(j.state(1));
      z.push(j.state(2));
      j.step();
    }
  cout << x.beginning <<" "<< x.cycle()<<endl;
  cout << y.beginning <<" "<< y.cycle()<<endl;
  cout << z.beginning <<" "<< z.cycle()<<endl;

  assert( (x.beginning == y.beginning) and
          (y.beginning == z.beginning) and
          (z.beginning == 1) );
  
  return smallestNumberThatIsDivisiblebyAllOther({x.cycle(), y.cycle(), z.cycle()});
}


unsigned long long int solutionB(string filename)
{return solutionB(Jupiter(filename));}
