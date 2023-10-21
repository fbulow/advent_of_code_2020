#include "solA.hh"

Flow SolA(std::function<Flow(Path)> const&  totalFlow, PathGenerator & pathGenerator)
{
  Flow ret{0};
  PathGenerator::Callback fcn = [&ret, &totalFlow]
		  (Path const &p)
		  {
		    auto x = totalFlow(p);
		    ret = std::max(ret, x);
		  };
  
  pathGenerator
    .callWithEach(fcn);
  return ret;
}
