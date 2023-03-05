#include "space.hh"
#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>


void washLine(string &s)
{
  for(char &c:s)
    switch(c)
      {
      case '-':
      case '>':
      case ',':
	c=' ';
      default:
	{}
      }
}

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


Space::Space(string const & filename)
  :Space([=](){
    ifstream in(filename);
    return Space(in);}())
{}
	     
Space::Space(istream &in)
{
  readInputFile(*this, in);
}

void getSequence_rec(vector<Coord> &ret, istream &in)
{
  int a,b;
  in>>a;
  if(in.eof()) return;
  in>>b;
  ret.emplace_back(Coord(a,b));
  getSequence_rec(ret, in);
}

vector<Coord> getSequence(string row)
{
  vector<Coord> ret;
  washLine(row);
  istringstream in(row);
  getSequence_rec(ret, in);
  return ret;
}

void readInputFile(Space &s, istream &in)
{
  string row;
  getline(in, row);

  if(in.eof()) return;

  s.drawSequence( getSequence(row) );

  readInputFile(s, in);
}

void Space::dropSnowflake(Coord c)
{
  try{
    dropSnowflake_(c);
  }catch(Done)
    {}
}

bool Space::hasHitTheFloor(Coord c) const
{
  if(c.y()>lowestPoint()) throw Done();
  return false;
}

void Space::dropSnowflake_(Coord c)
{
  if(hasHitTheFloor(c) or contains(c)) return; //Hit something done here!

  dropSnowflake_({c.x(), c.y()+1});
  dropSnowflake_({c.x()-1, c.y()+1});
  dropSnowflake_({c.x()+1, c.y()+1});

  //ok, we are on solid ground here.
  insert(c);
  return;
}

int Space::lowestPoint() const
{
  return max_element(begin(),
		     end(),
		     [](Coord const &a, Coord const &b)
		     {
		       return a.y()<b.y();
		     })->y();
}
