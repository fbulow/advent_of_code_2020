#pragma once

#include "path_generator.hh"
#include "regions.hh"
#include "distance.hh"
#include "path_iteration.hh"

class PathGeneratorImpl :PathGenerator
{
public:
  PathGeneratorImpl(Minutes total,
		    Distance distance,
		    Regions regions
		    )
    :total_	(total)
    ,distance_	(distance)
    ,regions_	(regions)
  {
  }

  void callWithEach(Callback& callback) override
  {
    pathIteration(callback,
		  total_,
		  distance_,
		  regions_,
		  "AA");
  }

private:
  Minutes total_;
  Distance distance_;
  Regions regions_;
  
};
