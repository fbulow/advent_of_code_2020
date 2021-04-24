#include "summation.hpp"
#include <cassert> 
#include <numeric>
#include <algorithm> 

Summation::Summation(vector<int> signal)
  :signal(move(signal))
{
}

unsigned int Summation::size(unsigned int stride)
{
  assert(stride>0);
  auto rest = (signal.size()-(stride-1));
  return 1+rest/stride + (rest%stride>0?1:0);
}
  
int Summation::operator()(unsigned int segment, unsigned int stride)
{
  assert(segment<size(stride));
  return 0;
}
