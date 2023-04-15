#pragma once
#include "types.hh"



class Navigator{
  Destinations destinations_;
  Valve location_;
public:
  Navigator(Destinations destinations, Valve start)
    :destinations_(move(destinations))
    ,location_(move(start))
  {}
  Destinations const & getDestinations() const
  {return destinations_;}
  Navigator goTo(Valve v) const;
  Valve getLocation() const
  {return location_;}
};
