#pragma once
#include<array>
#include<list>
#include<vector>
#include<cassert>
#include "position.hpp"

using namespace std;

class Door{
  Position a;
  Position b;
public:
  Door(Position const & a, Position const &b)
    :a(min(a,b))
    ,b(max(a,b))
  {
    assert(a!=b);
  }

  bool has(Position const &p) const
  {
    return (a==p) or (b==p);
  }
    
  
  auto operator<=>(Door const & other) const
  {
    auto r = a <=> other.a;
    if (r==0)
      return b <=> other.b;
    else
      return r;
  }
  bool operator==(Door const &other) const = default;
  Position other(Position const &p) const 
  {
    if(a==p)
      return b;
    else
      {
        assert (b==p);
        return a;
      }
  }
};

class Doors
{
  list<Door> data;
public:
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
