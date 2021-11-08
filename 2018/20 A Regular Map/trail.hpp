#pragma once
#include "position.hpp"
#include "doors.hpp"
#include <memory>

using namespace std;

struct Trail 
{
  Trail(Doors &d)
    :p(0,0)
    ,d(d)
  {}
  
  Trail(Trail &other)
    :p(other.p)
    ,d(other.d)
  {}
    
  Position p;
  Doors &d;

  void step(char dir)
  {
    operator()(dir);
  }
  void operator()(char dir)
  {
    d.push(p, p.step(dir));
    p=p.step(dir);
  }
};
