#pragma once
#include <cassert>
#include <map>
#include <set>
#include "types.hh"

using Valves = std::set<Valve>;

class Input : std::map<Valve, std::pair<Flow, std::set<Valve>>>
{
  friend Input example();
  friend int distance(Input const &inp, std::set<Valve> from, Valve to, int steps);
public:
  Flow flow(Valve v) const;

  [[nodiscard]]
  Valves adjacent(Valve const & v) const
  {
    for(auto &x: *this)
      if(x.first == v)
	return std::get<Valves>(x.second);
    assert(false);
  }  
};
