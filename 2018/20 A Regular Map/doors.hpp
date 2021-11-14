#pragma once
#include<array>
#include<list>
#include<vector>
#include<cassert>
#include<set>
#include "position.hpp"
#include <iostream>
#include <sstream>
#include "trail.hpp"
#include "textmap.hpp"
using namespace std;

class Door{
  Position a;
  Position b;
  friend class Doors;
public:
  Door(Position const & a, Position const &b);
  bool has(Position const &p) const;
  
  auto operator<=>(Door const & other) const
  {
    auto r = a <=> other.a;
    if (r==0)
      return b <=> other.b;
    else
      return r;
  }
  bool operator==(Door const &other) const = default;
  Position other(Position const &p) const ;
};

class Textmap;
class Doors
{
  list<Door> data;
  friend ostream& operator<<(ostream& out, Doors const &d);
  friend void Textmap::write_to(Doors &d);
    Position position{0,0};
public:
  Doors()=default;
  Doors(istream &in);
  Doors(string s);
  Doors(Textmap const &t);

  Position start_at() const;

  void push(Door d)
  {
    for(auto x:data)
      {
        if(d==x)
          return;
      }
    data.push_back(d);
  }
  void operator<<(Door p)
  {
    push(p);
  }

  void push(Position a, Position b)
  {
    push(Door(a,b));
  }

  set<Position> adjacent(Position const &p)
  {
    set<Position> ret;
      for_each(data.begin(),
               data.end(),
               [&ret, &p](auto const &x) {
                   if (x.has(p))
                       ret.insert(x.other(p));
               }
               );
      return ret;
  }
  vector<Position> pop(Position c)
  {
    vector<Position> ret;
    ret.reserve(4);
    for(auto it = data.begin(); it!=data.end();)
      {
        if(it->has(c))
          {
            ret.push_back(it->other(c));
            it = data.erase(it);
          }
        else
          it++;
      }
    return ret;
  }
    
};

ostream& operator<<(ostream& out, Doors const &d);
