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
  data =
    [this, c, val]{
      list<Cube> nextData;
      for(Cube const &target:data)
	for(Cube const &fragment: target.punchOut(c))
	  nextData.push_back(fragment);
      if(val)
	nextData.push_back(c);
      return nextData;
    }();
}
