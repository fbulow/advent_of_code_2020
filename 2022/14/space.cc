#include "space.hh"
#include <cassert>
#include <fstream>
#include <sstream>


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
