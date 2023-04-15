#pragma once
#include "types.hh"



class Navigator{
  Destinations destinations_;
public:
  Navigator(Destinations destinations)
    :destinations_(move(destinations))
  {}
  Destinations const & getDestinations() const
  {return destinations_;}
  Navigator goTo(Valve v) const;
};
