#pragma once
#include<optional>
#include<vector>
#include<cassert>
#include "result.hh"
#include "move.hh"

template<class BOARD>
Result Solver(BOARD const &b)
{
  if (b.isDone())
    return b.score();
  Result ret;
  for(auto const &x: b.moves())
    ret = std::min(ret, Solver(b.apply(x)));
  return ret;
}


