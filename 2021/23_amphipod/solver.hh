#pragma once
#include<optional>
#include<vector>
#include<cassert>
#include "result.hh"
#include "move.hh"

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
	ret = std::min(ret, Solver(b.apply(A::Move{})));
      return ret;
    }
}


