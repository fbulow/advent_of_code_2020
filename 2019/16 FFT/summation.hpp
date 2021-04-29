#pragma once
#include <vector> 
using namespace std;

class Summation
{
  vector<int> &integral;
public:
  Summation(vector<int> &signal);
  unsigned int size(unsigned int stride);

  int operator()(unsigned int segment, unsigned int stride);
};

unsigned int segmentStart(unsigned int segment, unsigned int stride);

