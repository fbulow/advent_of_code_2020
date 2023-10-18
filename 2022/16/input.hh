#pragma once
#include <map>
#include <set>
#include "types.hh"

class Input : std::map<Valve, std::pair<Flow, std::set<Valve>>>
{
  friend Input example();
  friend int distance(Input const &inp, std::set<Valve> from, Valve to, int steps);
public:
  Flow flow(Valve v) const;
};
