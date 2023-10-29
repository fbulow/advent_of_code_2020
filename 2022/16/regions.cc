#include "regions.hh"


Regions::Regions(Set all)
{
  for(auto const & v: all)
    data_[v]=Region::outer;
}

Regions Regions::startAt(Valve const &v) const
{
  auto ret = *this;

  ret.data_[v]=Region::edge;
    
  return ret;
}

Regions Regions::moveTo(Valve const &v) const
{
  auto ret = *this;
  for(auto &x:ret.data_)
    if(x.second==Region::edge)
      x.second=Region::inner;
  ret.data_[v] = Region::edge;
  return ret;
}

Regions Regions::moveTos(std::set<Valve> const &sv) const
{
  auto ret = *this;
  for(auto &x:ret.data_)
    if(x.second==Region::edge)
      x.second=Region::inner;
  for(auto &v: sv)
    ret.data_[v] = Region::edge;
  return ret;
  
}


Regions::Set filter(std::map<Valve, Regions::Region> const &d,
		    Regions::Region r)
{
  Regions::Set ret;
  for(auto const &x: d)
    if(x.second == r)
      ret.insert(x.first);
  return ret;

}

Regions::Set Regions::outer() const
{return filter(data_, Region::outer);}
Regions::Set Regions::edge()  const
{return filter(data_, Region::edge);}
Regions::Set Regions::inner() const
{return filter(data_, Region::inner);}

