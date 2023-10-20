#pragma once
#include "path.hh"
#include "types.hh"
#include "regions.hh"
#include <algorithm>

struct FromAndTo{
  Valve from;
  Valve to;
  Minutes distance;
};  
  
void pathIteration(auto ret,
		   Minutes remaining,
		   auto distance,
		   Regions r,
		   Path p={}
		   )
{
  if(remaining==0)
    return ret(p);

  std::vector<FromAndTo> fromAndTo;
  
  for(Valve const &  e: r.edge())
    for(Valve const &  o: r.outer())
      {
	auto d = distance(o,e);
	if(d<remaining)
	  fromAndTo.push_back({o, e, d});
      }
  if(fromAndTo.empty())
    return ret(p);
}
