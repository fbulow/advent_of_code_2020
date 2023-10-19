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
  

  Set outer() const {return outer_;}
  Set edge() const {return edge_;}
  
};
