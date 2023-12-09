#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include <vector>
using namespace std;

using Int = long long;

auto nextValue(vector<Int> v)
{
  if( all_of(v.begin(),
	     v.end(),
	     [](auto x){return x==0;}) )
    return Int(0);
  else
    {
      auto last = *v.rbegin();
      for(size_t i=1; i<v.size(); i++)
	v[i-1] = v[i]-v[i-1];
      v.resize(v.size()-1);
      return last + nextValue(v);
    }
}

template<auto nxtValue>
auto sol(istream &&in)
{
  Int ret = 0;
  string line;
  while(getline(in,line))
    if(!line.empty())
      {
	istringstream is(line);
	Int i;
	vector<Int> v;
	while(!(is>>i).fail())
	  v.push_back(i);
	ret += nxtValue(v);
      }
  return ret;
}
	 

auto solA(istream &&in)
{
  return sol<nextValue>(std::move(in));
}

auto solB(istream &&in)
{
  return sol<
    [](vector<Int> x)
    {
      reverse(x.begin(), x.end());
      return nextValue(x);
    }>(std::move(in));
}	     
  
