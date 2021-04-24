#pragma once
#include <vector> 
using namespace std;

class Summation
{
  vector<int> signal;
public:
  Summation(vector<int> signal);
  unsigned int size(unsigned int stride);

  int operator()(unsigned int segment, unsigned int stride);
};
