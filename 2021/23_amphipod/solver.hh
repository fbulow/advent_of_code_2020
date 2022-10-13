#pragma once
#include<optional>
#include<vector>
#include<cassert>
#include "result.hh"
#include "move.hh"

template<class BOARD>
Result Solver(BOARD const &b, Result ret={})
{
  if (b.score()>ret)
    return ret;
  else if (b.isDone())
    return b.score();
  for(auto const &x: b.moves())
    ret = std::min(ret, Solver(b.apply(x), ret));
  return ret;
}


