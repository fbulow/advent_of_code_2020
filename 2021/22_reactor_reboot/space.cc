#include "space.hh"

Space::Space()
    :vector<bool>(101*101*101, false)
  {}

unsigned int Space::countOn() const
{
  return count_if(cbegin(),
		  cend(),
		  [](auto x)->bool{return x;});
}

void Space::fill(Cube c, bool val)
  {
    c.x.min = max(c.x.min, -50);
    c.y.min = max(c.y.min, -50);
    c.z.min = max(c.z.min, -50);

    c.x.max = min(c.x.max,  50);
    c.y.max = min(c.y.max,  50);
    c.z.max = min(c.z.max,  50);
    
    for(int x = c.x.min; x<=c.x.max ; x++)
      for(int y =c.y.min; y<=c.y.max ; y++)
	for(int z =c.z.min; z<=c.z.max ; z++)
	  (*this)(x,y,z) = val;
  }

vector<bool>::reference Space::operator()(int x, int y, int z)
{
  return (*this)[(x+50)+101*((y+50)+101*(z+50))];
}
