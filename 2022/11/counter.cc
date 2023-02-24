#include "counter.hh"
#include <vector>

using namespace std;


void Counter::tick(size_t v)
{
  data[v]++;
}

int Counter::monkeyBusines() const
{
  vector<int> r;
  r.reserve(data.size());
  transform(data.cbegin(),
	    data.cend(),
	    back_inserter(r),
	    [](auto x){return x.second;});
    
  partial_sort(r.begin(),
	       next(r.begin(),2),
	       r.end(),
	       [](auto const & a, auto const & b){return b<a;});

  return r[0]*r[1];
}
