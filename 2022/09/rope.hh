#pragma once
#include"coord.hh"

class Rope{
  Coord head;
  Coord tail;
  
public:
  Coord step(char c);
};
