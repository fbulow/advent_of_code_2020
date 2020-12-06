#pragma once

#include <fstream>
#include <vector>
#include <set>
#include <numeric>
#include <cassert>
using namespace std;

vector<string> getRawInput(string const &filename)
{
  vector<string> ret;
  ifstream in(filename);
  assert(in.is_open());
  string line;
  while(getline(in, line))
    ret.push_back(line);
  return ret;
}

using Group=vector<string>;

vector<Group> group(vector<string> const & data)
{
  vector<Group> ret;

  auto a = data.begin();
  auto b = find(data.begin(), data.end(), "");
  assert(a!=b);

  while(b!=data.end())
    {
      ret.push_back({a, b});
      a=find_if(b, data.end(), [](auto const &a){return not a.empty();});
      b = find(next(a), data.end(), "");
    }
  ret.push_back({a, b});
  return ret;
}

struct Ans : public set<char>
{
  Ans()
  {}

  Ans(Ans const & other)
    :set<char>(other)
  {}
  
  Ans(string const &s)
    :set<char>(s.begin(), s.end())
  {}
  
  Ans unionWith(Ans const& other) const
  {
    Ans ret;
    set_union(cbegin(), cend(),
	      other.cbegin(), other.cend(),
	      inserter(ret, ret.begin()));
    return ret;
  }

  Ans intersectWith(Ans const& other) const
  {
    Ans ret;
    set_intersection(cbegin(), cend(),
		     other.cbegin(), other.cend(),
		     inserter(ret, ret.begin()));
    return ret;
  }
};

Ans reduceUnion(Group const &g)
{
  Ans ret;
  return reduce(g.cbegin(),
		g.cend(),
		ret,
		[](Ans const &a, Ans const &b){return a.unionWith(b);});
}

vector<Ans> agregateEach(vector<Group> const & data, auto reducer)
{
  vector<Ans> ret(data.size());
  transform(data.cbegin(), data.cend(),
	    ret.begin(),
	    reducer);
  return ret;
}

size_t reduceAndCount(vector<Group> const & data, auto reducer)
{
  vector<size_t> ret(data.size());
  transform(data.cbegin(), data.cend(),
	    ret.begin(),
	    [reducer](Group const &g){return reducer(g).size();});
  return accumulate( ret.begin(),
		     ret.end(),
		     0);
}

size_t reduceAndCount(string const &filename, auto reducer)
{
  return reduceAndCount(group(getRawInput(filename)), reducer);
}



int solution(vector<Ans> const &data)
{
  vector<int> s(data.size());
  transform(data.begin(),
	    data.end(),
	    s.begin(),
	    [](Ans const &x){return x.size();});
  return accumulate(s.begin(), s.end(), 0);
}


Ans stringIntersection(Ans const & a, string const & s)
{
  Ans ret{};
  Ans b(s);
  set_intersection(a.begin(), a.end(),
		   b.begin(), b.end(),
		   std::inserter(ret, ret.end()));
  return ret;
}

Ans reduceIntersect(Group const &g)
{
  Ans ret=g[0];
  assert(ret.size() != 0);
  return reduce(next(g.cbegin()),
		g.cend(),
		ret,
		[](Ans const &a, Ans const &b){return a.intersectWith(b);});
}

vector<Ans> getInputA(string const &filename)
{
  return agregateEach(group(getRawInput(filename)), reduceUnion);
}

vector<Ans> getInputB(string const &filename)
{
  return agregateEach(group(getRawInput(filename)), reduceIntersect);
}

