#include "get_message.hpp"
#include <numeric>
#include "offset.hpp" 

unsigned int get_message(vector<int> const & signal, unsigned int offset)
{
  auto i = next(signal.begin(), offset);
  return accumulate(i,
                    next(i,8),
                    (unsigned int) 0,
                    [](auto a, auto b){return 10*a+b;});
}

unsigned int get_message( vector<int> const & signal)
{
  return get_message(signal, offset(signal));
}
