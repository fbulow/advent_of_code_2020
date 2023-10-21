#pragma once
#include"types.hh"
#include<set>

class Regions{
  using Set = std::set<Valve>;
  Set outer_;
  Set edge_;
  Set inner_;
public:

  Regions(Set all);
  
  Regions startAt(Valve const &v) const;
  Regions moveTo(Valve const &v) const;

  Set outer() const;
  Set edge()  const;
  Set inner() const;
};
