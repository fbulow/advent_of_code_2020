#pragma once
#include <vector> 
using namespace std;

class Summation
{
  vector<int> &integral;
public:
  Summation(vector<int> &signal);
  unsigned int size(unsigned int stride) const;

  int operator()(unsigned int segment, unsigned int stride) const;
};

unsigned int segmentStart(unsigned int segment, unsigned int stride);

