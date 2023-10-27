#pragma once
#include <map>
#include <set>
#include "types.hh"

using Valves = std::set<Valve>;

class Input : std::map<Valve, std::pair<Flow, std::set<Valve>>>
{
  friend Input example();
  friend int distance(Input const &inp, std::set<Valve> from, Valve to, int steps);
public:
  [[nodiscard]]
  Flow flow(Valve v) const;

  [[nodiscard]]
  Valves adjacent(Valve const & v) const;

  [[nodiscard]]
  Valves nonzero() const;
};
