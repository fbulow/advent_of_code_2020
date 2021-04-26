#include "summation.hpp"
#include <cassert> 
#include <numeric>
#include <algorithm> 

Summation::Summation(vector<int> signal)
  :integral(move(signal))
{
  for(unsigned int i=1;i<integral.size();i++)
    integral[i]+=integral[i-1];
}

unsigned int Summation::size(unsigned int stride)
{
  assert(stride>0);
  auto rest = (integral.size()-(stride-1));
  return 1+rest/stride + (rest%stride>0?1:0);
}
  
int Summation::operator()(unsigned int segment, unsigned int stride)
{
  assert(segment<size(stride));

  if(0==segment)
    {
      if(stride==1)
        return 0;
      else
        return integral[stride-2];
    }
  else if (1==segment and stride==1)
    {
      return integral[0];
    }
  else if ( stride==1 )
    return integral[segment-1]-integral[segment-2];
  else
    return integral[segment]-integral[segment-1];
  assert(false);
}
