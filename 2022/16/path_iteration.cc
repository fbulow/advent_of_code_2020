#include "path_iteration.hh"

void pathIteration(Callback ret,
		   Minutes remaining,
		   Distance distance,
		   Regions r,
		   Path p
		   )
{
  if(remaining==0)
    {
      assert(!p.empty());
      return ret(std::move(p));
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
	return ret(std::move(p));
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

void pathIteration(Callback ret,
		   Minutes remaining,
		   Distance distance,
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
