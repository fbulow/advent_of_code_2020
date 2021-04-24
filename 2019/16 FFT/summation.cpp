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
  int total = signal.size();
  unsigned int ret{1};
  total-=(stride-1);
  while(total>0)
    {
      ret++;
      total-=stride;
        
    }
  return ret;
}
  
int Summation::operator()(unsigned int segment, unsigned int stride)
{
  assert(segment<size(stride));
  return 0;
}
