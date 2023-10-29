#pragma once
#include"types.hh"
#include<set>
#include<map>

class Regions{
public:
  using Set = std::set<Valve>;
  enum class Region {inner, edge, outer};

  Regions(Set all);
  
  Regions startAt(Valve const &v) const;
  Regions moveTo(Valve const &v) const;
  Regions moveTos(std::set<Valve> const &v) const;
  
  Set outer() const;
  Set edge()  const;
  Set inner() const;

  [[nodiscard]]
  std::set<Valve> allValves() const;
private:
  std::map<Valve, Region> data_;

};
