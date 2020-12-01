#include "solve.hpp"
#include <algorithm>

optional<int> solve(vector<int>::iterator first,
		    vector<int>::iterator end,
		    int pick, int magic_number)
{
  while(first != end)
    {
      if(pick>2)
	{
	  auto attempt=solve(next(first), end, pick-1, magic_number-*first);
	  if (attempt)
	    return (*first)*attempt.value();
	}
      else
	{
	  auto other = find_if(first,
			       end,
			       [first, magic_number](auto x){return x+(*first) == magic_number;});
	  if(other!=end)
	    return (*first)*(*other);
	}
      first++;
    }
  return {};
}
