#include "flood_fill.hh"

void floodFillRec(std::function<void(Valve, Minutes)> destAndRemaining,
	 std::function<Valves(Valve const &)> adjacent,
	 Regions const &r,
	 Minutes remaining
	 )
{
  if (remaining <= 0) return;

  std::set<Valve> allOuterAdjacent;
  
  for(auto const &e: r.edge())
    for(auto const &a : adjacent(e))
      if( ! r.inner().contains(a) )
	allOuterAdjacent.insert(a);

  for(auto const & aa: allOuterAdjacent)
    destAndRemaining(aa, remaining);

  floodFillRec(destAndRemaining,
      adjacent,
      r.moveTos(allOuterAdjacent),
      remaining-1);
}

void floodFill(FromToMinutesCallback ret,
	       Input const &data,
	       Valve const &startAt,
	       Minutes const total
	       )
{
  floodFillRec(
     [startAt, &ret, total]
     (Valve v, Minutes m)
     {
       ret(startAt, v, 1+total - m);
     },
     [data]
     (Valve const &v)
     {return data.adjacent(v);},
     Regions(data.allValves()).moveTo(startAt),
     total
     );
}
