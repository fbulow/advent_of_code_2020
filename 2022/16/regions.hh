#pragma once
#include"types.hh"
#include<set>

class Regions{
public:
  using Set = std::set<Valve>;
  Set outer_;
  Set edge_;
  Set inner_;

  Regions(Set all)
    :outer_(std::move(all))
  {}

  Regions startAt(Valve const &v) const
  {
    auto ret = *this;
    ret.outer_.erase(v);
    ret.edge_.insert(v);
    
    return ret;
  }
  Regions moveTo(Valve const &v) const
  {
    Regions ret({});
    for(auto const &x: inner_)
      ret.inner_.insert(x);
    for(auto const &x: edge())
      ret.inner_.insert(x);
    ret.edge_.insert(v);
    for(auto const &x: outer())
      if(x!=v)
	ret.outer_.insert(x);
    
    return ret;
  }

  Set outer() const {return outer_;}
  Set edge()  const {return edge_;}
  Set inner() const {return inner_;}
};
