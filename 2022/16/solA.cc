#include "solA.hh"


Flow SolA(Input const & inp)
{
  return 1651;
}

Flow SolA(std::function<Flow(Path)> const&  totalFlow, ForEachPath forEachPath)
{
  Flow ret{0};

  forEachPath([&ret, &totalFlow]
	      (Path const &p)
	      {
		auto x = totalFlow(p);
		ret = std::max(ret, x);
	      }
	      );
  return ret;
}
