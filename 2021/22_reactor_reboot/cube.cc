#include "cube.hh"

long long Cube::size() const { return x.size()*y.size()*z.size();}

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

bool Cube::contains(Point const &p) const
{
  return
    x.contains(p.x) and
    y.contains(p.y) and
    z.contains(p.z) ;
}

Point Cube::centre() const
{return {x.centre(), y.centre(), z.centre()};}


set<Cube> Cube::punchOut(Cube const & tr) const
{
  bool miss{true};
  set<Cube> ret;
  for(auto const x:splitBy(tr))
    {
      if(not tr.contains(x.centre()))
	ret.insert(x);
      else
	miss=false;
    }
  if(miss)
    return {*this};
  else
    return ret;
}
