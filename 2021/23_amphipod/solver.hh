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
    {
      auto r = b.score();
      return r;
    }
  auto m = b.moves();
  if(m.empty())
    return {};
  
  for(auto const &x: m)
    ret = std::min(ret, Solver(b.apply(x), ret));
  return ret;
}
