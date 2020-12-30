#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
using namespace std;

struct Coord{
  int south{0};
  int east{0};
  Coord operator+(Coord const &other ) const
  {
    Coord ret = *this;
    ret+=other;
    return ret;
  }
  void operator+=(Coord const &other )
  {
    south+=other.south;
    east+=other.east;
  }
  auto operator<=>(const Coord&) const = default;
  
};
ostream& operator<<(ostream &cout, Coord const &c)
{
  cout<<"{"<<c.south<<", "<<c.east<<"}";
  return cout;
}


enum class Di{e, se, sw, w, nw, ne};

Coord step(Coord start, Di d)
{
  switch(d)
    {
    case (Di::e):
      start.east+=2;
      return start;
    case (Di::w):
      start.east-=2;
      return start;
    case (Di::se):
      start.south+=1;
      start.east+=1;
      return start;
    case (Di::nw):
      start.south-=1;
      start.east-=1;
      return start;
    case (Di::sw):
      start.south+=1;
      start.east-=1;
      return start;
    case (Di::ne):
      start.south-=1;
      start.east+=1;
      return start;
      
    }
  assert(false);
}

template<class T=initializer_list<Di>&&>
Coord step(T navlist)
{
  Coord ret;
  for(Di d:navlist)
    ret=step(ret, d);
  return ret;
}

struct Nav : vector<Di>
{
  Nav(string const &s)
  {
    reserve(s.size());
    istringstream cin(s);
    optional<char> prefix{};
    char c;
    while(not(cin>>c).eof())
      {
        if(prefix)
          {
            if(prefix.value()=='s' and c=='e')
              push_back(Di::se);
            else if(prefix.value()=='s' and c=='w')
              push_back(Di::sw);
            else if(prefix.value()=='n' and c=='e')
              push_back(Di::ne);
            else if(prefix.value()=='n' and c=='w')
              push_back(Di::nw);
            prefix={};
          }
        else if(c=='n' or c=='s')
          prefix=c;
        else if(c=='e')
          push_back(Di::e);
        else if (c=='w')
          push_back(Di::w);
      }
  }
};

struct BlackTiles : set<Coord>
{
  BlackTiles() = default;
  BlackTiles(string const & filename)
  {
    ifstream cin(filename);
    assert(cin.is_open());

    string line;
    while(getline(cin, line))
        toggle(step(Nav(line)));
  }

  void toggle(Coord c)
  {
    if(contains(c))
      erase(c);
    else
      insert(c);
  }

  bool black(Coord c) const
  {
    return contains(c);
  }
  bool white(Coord c) const
  {
    return not black(c);
  }
  
  auto countBlack() const
  {
    return size();
  }

  void nextDay();
  
};

unsigned int solutionA(string const &filename)
{
  return BlackTiles(filename).countBlack();
}

struct Heat:map<Coord, int>
{
  void black(Coord c)
  {
    auto &t = *this;
    t[c]; //To assure existence! t[c]==0 is relevant if c is black.
    for (auto x:{Di::e, Di::se, Di::sw, Di::w, Di::nw, Di::ne})
      t[step(c, x)]++;
  }

  Heat(BlackTiles const &iteratable)
  {
    for(auto x: iteratable)
      black(x);
  }
};

void BlackTiles::nextDay()
{
  deque<Coord> toToggle;
  for(auto [coord, count] : Heat(*this))
    {
      if( black(coord) and ( (count == 0) or (count > 2 ) ))
        toToggle.push_back(coord);
      else if (white(coord) and (count ==  2 ) )
        toToggle.push_back(coord);
    }
  for(auto c:toToggle)
    toggle(c);
}

auto solutionB(string filename)
{
  BlackTiles ret(filename);
  for(int i=0;i<100;i++)
    ret.nextDay();
  return ret.countBlack();
}
