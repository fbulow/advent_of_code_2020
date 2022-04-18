#include "square_space.hh"
#include <numeric>
unsigned int SquareSpace::countOn() const
{
  return accumulate(data.cbegin(),
		    data.cend(),
		    0,
		    [](long a,
		       Cube const &b)
		    {
		      return a+b.size();
		    });
}

void SquareSpace::fill(Cube c, bool val)
{
  if(val)
    data.push_back(c);
}
