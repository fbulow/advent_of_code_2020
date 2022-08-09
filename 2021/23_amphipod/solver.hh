#pragma once
#include<optional>
#include<vector>
#include<cassert>

template<class BOARD>
std::optional<int> Solver(BOARD const &b)
{
  auto m = b.moves();
  if(m.empty())
    {
      if (b.isDone())
	return {b.score()};
      else
	return {};
    }
  else
    {
      return Solver(b.apply({}));
    }
}


