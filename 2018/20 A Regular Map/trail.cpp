#include "trail.hpp"
#include "doors.hpp"

Trail::Trail(Doors &d)
  :p(0,0)
  ,d(d)
{}

Trail::Trail(Trail &other)
  :p(other.p)
  ,d(other.d)
{}

void Trail::operator()(char dir)
  {
    d.push(p, p.step(dir));
    p=p.step(dir);
  }
