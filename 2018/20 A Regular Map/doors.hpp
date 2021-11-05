#pragma once
#include<array>
#include<list>
#include<vector>
#include<cassert>
#include "position.hpp"

using namespace std;

class Doors
{
  list<array<Position, 2>> data;
public:
  void add(Position a, Position b)
  {
    assert(not (a==b));
    for(auto x:data)
      {
        if (x == array<Position, 2>({a,b}) or
            x == array<Position, 2>({b,a}))
          return;
      }
    data.push_back({a,b});
  }

  vector<Position> pop(Position c)
  {
    vector<Position> ret;
    ret.reserve(4);
    for(auto it = data.begin(); it!=data.end();)
      {
        if((*it)[0]==c)
          {
            ret.push_back((*it)[1]);
            it = data.erase(it);
          }
        else if((*it)[1]==c)
          {
            ret.push_back((*it)[0]);
            it = data.erase(it);
          }
        else
          it++;
      }
    return ret;
  }
    
};
