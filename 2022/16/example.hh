#pragma once
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <string>
#include <cassert>


using Flow = int;
using Valve = std::string;
using Time = int;

class Input;
Input  example();

class Input : std::map<Valve, std::pair<Flow, std::set<Valve>>>
{
  friend Input example();
  friend int distance(Input const &inp, std::set<Valve> from, Valve to, int steps);
public:
  Flow flow(Valve v) const;
};

class Score{
public:
  Score() = default;
  Score log(Time time, Flow flow) const;
  int total() const;
private:
  Score(Time t, Flow f, int sum);
  
  Time t{0};
  Flow f{0};
  int sum{0};
};


inline
int distance(Input const &inp, std::set<Valve> from, Valve to, int steps)
{
  if(from.contains(to))
    return steps;
  else
    {
      auto nxt = from;
      for(auto v: from)
	for(auto vv: inp.at(v).second)
	  nxt.insert(vv);
      assert(nxt.size() > from.size());
      return distance(inp, nxt, to, steps+1);
    }
}

inline
int distance(Input const &inp, Valve from, Valve to)
{
  return distance(inp, {from}, to, 0);
}
