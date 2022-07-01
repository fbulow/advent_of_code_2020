#include<iostream>
#include<fstream>
#include<sstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
#include<memory>
#include"strong_type.hpp"
#include<set>
#include<map>
#include<iterator>
using namespace std;

enum struct Fold{x,y};

struct Coord{
  int x;
  int y;
  int& operator[](Fold f) 
  {
    switch(f)
      {
      case Fold::x:
        return x;
      case Fold::y:
        return y;
      }
    assert(false);
  }
};
  
bool operator<(Coord lhs, Coord rhs)
{
  if(lhs.x==rhs.x)
    return rhs.y<lhs.y;
  else
    return rhs.x<lhs.x;
}

struct Line{
  Fold f;
  int value;
};


struct Data{
  set<Coord> dots;
  vector<Line> lines;
  
};

ostream& operator<<(ostream& out, set<Coord> const & s)
{
  auto const xMax = 1+max_element(s.cbegin(),
                                  s.cend(),
                                  [](Coord a, Coord b)
                                  {
                                    return a.x<b.x;
                                  })->x;
  auto const yMax = 1+ max_element(s.cbegin(),
                                   s.cend(),
                                   [](Coord a, Coord b)
                                   {
                                     return a.y<b.y;
                                   })->y;
  auto const xMin = min_element(s.cbegin(),
                                s.cend(),
                                [](Coord a, Coord b)
                                {
                                  return a.x<b.x;
                                })->x;
  auto const yMin = min_element(s.cbegin(),
                                s.cend(),
                                [](Coord a, Coord b)
                                {
                                  return a.y<b.y;
                                })->y;
  
  for(int y = yMin;y<yMax;y++)
    {
      for(int x = xMin;x<xMax;x++)
        if(s.contains({x,y}))
          out<<'#';
        else
          out<<'.';
      cout<<endl;
    }
  
  return out;
}

set<Coord> fold(set<Coord> const & s, Line const &l)
{
  set<Coord> ret;
  for(auto c:s)
    {
      if(c[l.f] > l.value)
        c[l.f] = l.value - (c[l.f]-l.value) ;
      ret.insert(c);
    }
  return ret;
}

Fold get_line_dimmension(string const &line)
{
  switch(line[11])
    {
    case 'x':
      return Fold::x;
    case 'y':
      return Fold::y;
    default:
      assert(false);
    }
}


Data input(istream& cin)
{
  Data ret;
  string line;
  getline(cin, line);
  while(line!="")
    {
      istringstream in(line);
      int x,y;
      char c;
      in>>x>>c>>y;
      ret.dots.insert({x,y});
      getline(cin, line);
    }
  getline(cin, line);
  while(not cin.eof())
    {
      istringstream in(string(next(line.begin(), 13), line.end()));
      int v;
      in>>v;
      ret.lines.push_back(
                          Line{
                            get_line_dimmension(line),
                            v});

      getline(cin, line);
    }    
  
  return ret;
}

auto solution_a(Data const &in)
{
  return fold(in.dots, in.lines[0]).size();
}

ostream& operator<<(ostream& out, Line const &l)
{
  if(l.f == Fold::x)
    out<<"x=";
  else
    out<<"y=";
  out << l.value;
  return out;
}

auto solution_b(Data in)
{
  auto dots = in.dots;
  cout<<"in.lines[0] "<<in.lines[0]<<endl;
  for(Line l: in.lines)
      dots = fold(dots, l);
  ostringstream out;
  out<<endl<<dots;
  return out.str();
}


