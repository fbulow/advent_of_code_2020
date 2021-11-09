#pragma once
#include "position.hpp"
#include "doors.hpp"
#include <memory>

using namespace std;

class Doors;

struct Trail 
{
  Trail(Doors &d);
  
  Trail(Trail &other);
    
  Position p;
  Doors &d;

  void step(char dir)
  {
    operator()(dir);
  }
  void operator()(char dir);
};
