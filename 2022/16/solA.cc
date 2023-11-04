#include "solA.hh"


Flow SolA(Input const & inp)
{
  constexpr Minutes totalTime = 30;
  Flow ret = 0;

  Flow ret{0};
  allSequenceOfOpenings([&ret, &totalFlow]
	      (Path const &p)
	      {
		auto x = totalFlow(p);
		ret = std::max(ret, x);
	      });
  
  return ret;
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
