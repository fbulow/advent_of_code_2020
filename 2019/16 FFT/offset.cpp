#include "offset.hpp"
#include <numeric> 
unsigned int offset(vector<int> const & signal)
{
  auto i = signal.begin();
  return accumulate(signal.begin(),
                    next(signal.begin(), 7),
                    (unsigned int) 0,
                    [](auto a, auto b){return a+b;});
}
