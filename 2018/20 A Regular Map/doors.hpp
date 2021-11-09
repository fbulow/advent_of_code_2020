#pragma once
#include<array>
#include<list>
#include<vector>
#include<cassert>
#include "position.hpp"
#include <iostream>
#include <sstream>
#include "trail.hpp"

using namespace std;

class Door{
  Position a;
  Position b;
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

class Doors
{
  list<Door> data;
  friend ostream& operator<<(ostream& out, Doors const &d);

public:
  Doors()=default;
  Doors(istream &in);
  Doors(string s);
  
  void push(Door d)
  {
    for(auto x:data)
      {
        if(d==x)
          return;
      }
    data.push_back(d);
  }
  void push(Position a, Position b)
  {
    push(Door(a,b));
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
