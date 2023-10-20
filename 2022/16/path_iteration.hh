#pragma once
#include "path.hh"
#include "types.hh"
#include "regions.hh"
#include <algorithm>
#include <cassert>

struct FromAndTo{
  Valve from;
  Valve to;
  Minutes distance;
};  



void pathIteration(auto ret,
		   Minutes remaining,
		   auto distance,
		   Regions r,
		   Path p
		   )
{
  if(remaining==0)
    {
      assert(!p.empty());
      return ret(p);
    }

  std::vector<FromAndTo> fromAndTo;
  
  for(Valve const &  e: r.edge())
    for(Valve const &  o: r.outer())
      {
	auto d = distance(e,o);
	if(d<remaining)
	  fromAndTo.push_back({e, o, d});
      }
  if(fromAndTo.empty())
    {
      if(!p.empty()) //i.e. Chose not to open first valve but can't go anywhere
	return ret(p);
    }
  else
    {
      for(auto & x : fromAndTo)
	pathIteration(ret,
		      remaining - x.distance - 1,
		      distance,
		      r.moveTo(x.to),
		      p.moveTo(x.distance, x.to)
		      );
    }
}


void pathIteration(auto ret,
		   Minutes remaining,
		   auto distance,
		   Regions r,
		   Valve const &v
		   )
{
  Path p;
  //Open first valve
  pathIteration(ret,
		remaining-1,
		distance,
		r.startAt(v),
		p.moveTo(0, v)
		);
  //Do not open firt valve
  pathIteration(ret,
		remaining,
		distance,
		r.startAt(v),
		std::move(p)
		);
}
