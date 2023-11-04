#include "solA.hh"


Flow SolA(Input const & inp)
{
  constexpr Minutes totalTime = 30;
  Flow ret = 0;

  
  
  allSequenceOfOpenings([&ret, &totalFlow]
	      (Path const &p)
	      {
		ret = std::max(ret, 
	      });
  
  return ret;
}

Flow SolA(std::function<Flow(Path)> const&  Totalflow, ForEachPath forEachPath)
{
  Flow ret{0};

  forEachPath([&ret, &totalFlow]
	      (Path const &p)
	      {
		auto x = totalVolume();
		ret = std::max(ret, x);
	      }
	      );
  return ret;
}
