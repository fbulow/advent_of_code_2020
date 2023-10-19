#pragma once
#include "path.hh"
#include "types.hh"
#include "regions.hh"
#include <algorithm>

struct FromAndTo{
  Valve from;
  Valve to;
};  
  


void pathIteration(auto ret,
		   Minutes remaining,
		   auto distance,
		   Regions r,
		   Path &p
		   )
{
  if(remaining==0)
    return ret(p);

  std::vector<FromAndTo> fromAndTo;
  
  for(Valve const &  e: r.edge())
    for(Valve const &  o: r.outer())
      if(distance(o,e)<=remaining)
	fromAndTo.push_back({o,e});
  if(fromAndTo.empty())
    return ret(p);
}

void pathIteration(auto ret,
		   Minutes remaining,
		   auto distance,
		   Regions r
		   )
{
  Path p;
  pathIteration(ret, remaining, distance, r, p);
}
