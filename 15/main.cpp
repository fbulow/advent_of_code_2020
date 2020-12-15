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
class Spoken: public list<I>
{
  map<I,I> data; //spoken -> last said
  I stepNr{1};
  I lastSpoken;
public:
  template<class ... A>
  Spoken(A...args)
    :list<I>{(I) args...}
    ,data{}
  {
    lastSpoken = *rbegin();
    pop_back();
    for(auto spoken: *this)
	data[spoken] = stepNr++;
  }

  I nr()
  {
    return stepNr;
  }
  
  void turn()
  {
    auto &x = data[lastSpoken];
    if(0==x)
      {
	data[lastSpoken] = stepNr;
	lastSpoken = 0;
      }
    else
      {
	lastSpoken = stepNr-x;
	x=stepNr;
      }
    stepNr++;
  }
  I last() const
  {
    return lastSpoken;
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
  while(s.nr()<2020)
    s.turn();
  return s.last();
}

I solveB(Spoken s)
{
  while(s.nr()<30000000)
    s.turn();
  return s.last();
}
