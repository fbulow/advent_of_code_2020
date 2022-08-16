#pragma once
#include<optional>
#include<vector>
#include<cassert>
#include "result.hh"

template<class BOARD>
Result Solver(BOARD const &b)
{
  auto m = b.moves();
  if(m.empty())
    {
      if (b.isDone())
	return b.score();
      else
	return {};
    }
  else
    {
      Result ret;
      for(auto const &x: m)
	{
	  ret = Solver(b.apply({}));
	}
      return ret;
    }
}


