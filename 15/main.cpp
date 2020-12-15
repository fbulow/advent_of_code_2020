#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
using namespace std;

using I = unsigned int;
struct Spoken: list<I>
{
  template<class ... A>
  Spoken(A...args)
    :list<I>{(I) args...}
  {}
  
  void turn()
  {
    auto value = last();
    auto last = find(next(rbegin()),
		     rend(),
		     value);
    if(last==rend())
      push_back(0);
    else
      push_back(distance(rbegin(), last));
  }
  I last() const
  {
    return *rbegin();
  }
};
ostream& operator<<(ostream& cout, Spoken const &s)
{
  for(auto x: s)
    cout<<x<<" ";
  return cout;
}
  
I solveA(Spoken s)
{
  while(s.size()<2020)
    s.turn();
  return s.last();
}
