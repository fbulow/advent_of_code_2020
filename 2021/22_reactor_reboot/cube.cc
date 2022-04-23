#include "cube.hh"

long Cube::size() const { return x.size()*y.size()*z.size();}

bool operator<(Cube const &a, Cube const &b)
{
  if(a.x<b.x)
    return true;
  else if(b.x<a.x)
    return false;
  if(a.y<b.y)
    return true;
  else if(b.y<a.y)
    return false;
  if(a.z<b.z)
    return true;
  else
    return false;
}


set<Cube> Cube::splitBy(Cube const & tr) const
{
  set<Cube> ret;
  for(auto rx: x.splitBy(tr.x) )
    for(auto ry: y.splitBy(tr.y) )
      for(auto rz: z.splitBy(tr.z) )
	ret.insert({rx,ry,rz});
  return ret;
}
