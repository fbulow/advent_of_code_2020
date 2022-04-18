#pragma once
#include<vector>
#include"cube.hh"
using namespace std;

struct Space: vector<bool>
{
  Space();

  unsigned int countOn() const;

  void fill(Cube c, bool val);
  
  vector<bool>::reference operator()(int x, int y, int z);
}; 
