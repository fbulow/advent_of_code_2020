#include "regions.hh"


Regions::Regions(Set all)
  :outer_(std::move(all))
{}

Regions Regions::startAt(Valve const &v) const
{
  auto ret = *this;
  ret.outer_.erase(v);
  ret.edge_.insert(v);
    
  return ret;
}
Regions Regions::moveTo(Valve const &v) const
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

Regions::Set Regions::outer() const {return outer_;}
Regions::Set Regions::edge()  const {return edge_;}
Regions::Set Regions::inner() const {return inner_;}
