#include "input.hh"
#include <cassert>
#include <ranges>


Valves Input::nonzero() const
{
  using namespace std::views;
  Valves ret;
  for(auto &x:
	static_cast<std::map<Valve, std::pair<Flow, std::set<Valve>>> const &>(*this)
	|filter([](auto const &x){return std::get<Flow>(x.second)>0;}))
    ret.insert(x.first);
  return ret;
}

Valves Input::adjacent(Valve const & v) const
{
  for(auto &x: *this)
    if(x.first == v)
      return std::get<Valves>(x.second);
  assert(false);
}
