#include "total_volume.hh"
#include <numeric>

Flow totalVolume(Path const & p, FlowRates const & flowRates, Minutes remaining)
{
  return std::accumulate(p.begin(),
			 p.end(),
			 Flow(0),
			 [flowRates, remaining](Flow acc, Event const & a)
			 {
			   return acc+flowRates.at(a.open)*(remaining - a.timePassed) ;
			 });
}
