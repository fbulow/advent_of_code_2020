#pragma once
#include <vector>
#include "types.hh"

struct Event{
  Minutes timePassed;
  Valve open;
};

class Path
{
  std::vector<Event> d;
public:
  Path(std::vector<Event> &&x = {})
    :d(std::forward<std::vector<Event>>(x))
  {}
  auto size() const {return d.size();}
  auto empty() const { return d.empty();}
  auto begin() {return d.begin();}
  auto end() {return d.end();}
  auto begin() const {return d.begin();}
  auto end() const {return d.end();}

  auto& operator[](auto i){return d[i];}
  auto const & operator[](auto i) const {return d[i];}

  Path moveTo(Minutes timeToGetToValve, Valve v)
  {
    auto ret = *this;
    if(ret.empty())
      {
	ret.d.push_back({timeToGetToValve+1, v});
	return ret;
      }
    else
      {
	ret.d.push_back(
			{
			  ret.d.rbegin()->timePassed+timeToGetToValve+1,
			  v});
	return ret;
      }
  }
};
