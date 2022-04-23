#pragma once
#include<list>
#include"cube.hh"
using namespace std;

struct SquareSpace{
  list<Cube> data;

  void fill(Cube c, bool val);
  
  long long countOn() const;
    
};

