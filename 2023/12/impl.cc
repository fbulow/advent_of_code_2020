#include <algorithm>
#include <fstream>
#include <initializer_list>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include <vector>
#include <functional>

using namespace std;

bool isAMatch(char is, char isNot)
{
  return is =='?' || isNot=='?' || is != isNot ;
}

bool isAMatch(string_view row, string_view isNot)
{
  assert(row.size()==isNot.size());
  for(size_t i = 0; i<row.size(); i++)
    if(!isAMatch(row[i], isNot[i]))
      return false;
  return true;
}

void forAllPermutations(function<void()> callback,
                        auto sBegin,
			auto sEnd,
			auto gBegin,
			auto gEnd)
{
  if(gBegin==gEnd)
    callback();
  
  
}

void forAllPermutations(function<void(string const &s)> callback,
			string s,
			vector<int> const &groupSizes)
{
  auto cb = [&callback, &s]()
  {
    callback(s);
  };
  
  
  forAllPermutations(cb,
		     s.begin(),
		     s.end(),
		     groupSizes.begin(),
		     groupSizes.end());
}
