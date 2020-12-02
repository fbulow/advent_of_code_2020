#include "solve.hpp"
#include <algorithm>
#include <cassert>
optional<int> solve(vector<int>::iterator first,
		    vector<int>::iterator end,
		    int pick, int magic_number)
{
  assert(pick>0);
  if(first==end) return {};
    
  if(pick==1)
    {
      if( end != find(first,
		      end,
		      magic_number))
	return magic_number;
      else
	return {};
    }
  else
    {
      auto attempt=solve(next(first), end, pick-1, magic_number-*first);
      if(attempt)
	return ((*first) * attempt.value());
      else
	return solve(next(first), end, pick, magic_number);
    }
}
