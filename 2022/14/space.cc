#include "space.hh"
#include <cassert>

void Space::drawLine(int x0, int y0, int x1, int y1)
{
  if(x0==x1)
    {
      assert(y0!=y1);
      auto ymax = max(y0,y1);
      for(auto y=min(y0,y1);y<=ymax; y++)
	insert(Coord(x0, y));
    }
  else
    {
      assert(x0!=x1);
      auto xmax = max(x0,x1);
      for(auto x=min(x0,x1);x<=xmax; x++)
	insert(Coord(x, y0));
    }
}


void Space::drawLine(Coord const &from, Coord const &to)
{
  drawLine(from.x(), from.y(), to.x(), to.y());
}

void rec(Space &s, Coord const & head, auto beg, auto end)
{
  if(beg!=end)
    {
      s.drawLine(head, *beg);
      rec(s, *beg, next(beg), end);
    }
}


void Space::drawSequence(vector<Coord> const &s)
{
  auto beg = s.begin();
  auto end = s.end();
  assert(beg!=end);
  rec(*this, *beg, next(beg), end);
}
