#pragma once
#include "types.hh"
#include "distance.hh"



class Navigator{
  Destinations destinations_;
  Valve location_;
  Steps steps_;
  int distance_;
public:
  Navigator(Destinations destinations, Valve start, Steps steps)
    :destinations_(move(destinations))
    ,location_(move(start))
    ,steps_(steps)
  {}
  Destinations const & getDestinations() const
  {return destinations_;}
  Navigator goTo(Valve v) const;
  Valve getLocation() const
  {return location_;}

  void add(Distance const &d)
  {
    distance_=d.minutes;
  }
  
  Steps getSteps() const
  {return steps_;}
};
