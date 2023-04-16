#include "navigator.hh"
#include <cassert>
#include <ranges>
#include <algorithm>

Navigator Navigator::goTo(Valve v) const
{
  return Navigator(
		   [this, v] //Evaluated immediately!
		   {
		     assert( ! destinations_.empty() );
		     Destinations ret;
		     ret.reserve(destinations_.size()-1);
		     ranges::copy_if(destinations_, back_inserter(ret), [v](auto x){return x!=v;});
		     return ret;
		   }(),
		   v,
		   getSteps()-distance_-1
		   );
}
