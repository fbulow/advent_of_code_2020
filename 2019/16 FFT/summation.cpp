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
unsigned int segmentStart(unsigned int segment, unsigned int stride)
{
  assert(segment>0); //fist one has no start.
  if(stride==1)
    return segment-1;
  else
    return stride*segment-1;//stride*(segment-1) + (stride-1);
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
  else
    {
      auto const start = segmentStart(segment, stride);
      if(0==start)
        return integral[stride-1];
      else if (start == (integral.size()-1))
        return integral[1]-integral[0];
      auto const end   = start + stride;
      if(end >= integral.size())
        return integral.back() - integral[start - 1];


      assert(false);
    }
}
