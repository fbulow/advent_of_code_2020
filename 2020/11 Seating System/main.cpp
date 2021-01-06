#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
#include <functional>
#include <boost/algorithm/string.hpp> 

using namespace std;

using I = unsigned long int;

struct Dir
{
  int row{0};
  int column{0};
};

struct Coord
{
  size_t row{0};
  size_t column{0};

  Coord& operator+=(Dir const &d)
  {
    row+=d.row;
    column+=d.column;
    return *this;
  }
};

template<class T>
class Grid
{
protected:
  size_t Nrows{0};
  size_t Ncolumns{0};
  vector<T> data;
public:
  Grid(size_t Nrows,
       size_t Ncolumns)
    :Nrows{Nrows}
    ,Ncolumns{Ncolumns}
  {
    data.resize(Nrows*Ncolumns);
  }

  
  Grid(deque<string> const & lines)
    :Grid(lines.size(),
          lines.front().size())
  {
    data.resize(Nrows*Ncolumns);
    auto it = data.begin();
    for(string const &row: lines)
      it = copy(row.begin(), row.end(), it);
  }

  size_t countRows() const
  {
    return Nrows;
  }
    
  size_t countColumns() const
  {
    return Ncolumns;
  }
  
  T& operator[](Coord const &c)
  {
    assert(c.row< Nrows);
    assert(c.column< Ncolumns);

    return data[c.row*Ncolumns + c.column];
  }
  T const & operator[](Coord const &c) const
  {
    assert(c.row< Nrows);
    assert(c.column< Ncolumns);

    return data[c.row*Ncolumns + c.column];
  }

  auto begin()
  {
    return data.begin();
  }
  auto end()
  {
    return data.end();
  }
  
};


class Room : public Grid<char>
{
public:
  friend bool     operator==(Room const &a, Room const &b);
  friend ostream& operator<<(ostream& out, Grid<char> const &g);
  Room(string filename)
    :Room([filename]()
    {
      ifstream in(filename);
      assert(in.is_open());
      return in;
    }())
  {}
  
  Room(istream &&in)
    :Room([this](istream &&in) //evaluated immediately
    {
      string line;
      deque<string> lines;
      assert(getline(in, line));
      assert(line.size()!=0);
      Ncolumns = line.size();
      lines.push_back(line);
    
      while(getline(in, line))
        {
          if(not line.empty())
            {
              lines.push_back(line);
            }
        }
      return lines;
    }(move(in)))
  {}

  Room(deque<string> const &lines)
    :Grid<char>(lines)
  {}
  
  unsigned int count(char c) const
  {
    return std::count(data.cbegin(),
                      data.cend(),
                      c);
  }
  
  bool inRoom(Coord const &c) const
  {
    return (c.row<Nrows) and (c.column<Ncolumns);
  }
  
  char visible(Coord c, Dir const &d) const 
  {
    c+=d;
    while(inRoom(c))
      {
        if( (*this)[c]!='.' )
          return (*this)[c];
        c+=d;
      }
    return '.';
  }
  
  unsigned int countVisible(Coord c, char state='#')
  {
    array<Dir,8> const directions({{0,1}, {0, -1},
                                   {1,0}, {-1, 0},
                                   {1,1}, {-1,1}, {1,-1}, {-1,-1}});

    
    return count_if(directions.cbegin(),
                    directions.cend(),
                    [this, c, state](Dir const &dir)
                    {
                      return visible(c, dir)==state;
                    });
    
  }
};

bool operator==(Room const &a, Room const &b)
{
  return a.data==b.data;
}

ostream& operator<<(ostream& out, Grid<char> const &g)
{
  out<<endl;
  for(size_t row=0;row<g.countRows();row++)
    {
      for(size_t column=0;column<g.countColumns();column++)
        out<<g[{row, column}];
      out<<endl;
    }
  return out;
}
ostream& operator<<(ostream& out, Room const &r)
{
  return out<<static_cast<Grid<char>>(r);
}

struct Cell
{
  char current;
  unsigned int countOccupied;

  char nextState() const
  {
    if(current=='L' and countOccupied==0)
      //If a seat is empty (L) and there are no occupied seats
      //adjacent to it, the seat becomes occupied.
      return '#';
    else if(current=='#' and countOccupied>=5)
      //If a seat is occupied (#) and four or more seats adjacent to
      //it are also occupied, the seat becomes empty.
      return 'L';
    else
      //Otherwise, the seat's state does not change.
      return current;
  }
};

Room step(Room r)
{
  Grid<Cell> heat(r.countRows(), r.countColumns());
  for(size_t row=0; row< r.countRows(); row++)
    for(size_t column=0; column< r.countColumns(); column++)
      {
        Coord c{row,column};
        heat[c] = Cell(r[c], r.countVisible(c,'#'));
      }

  transform(heat.begin(),
            heat.end(),
            r.begin(),
            [](Cell const &c){return c.nextState();});
  return r;
}

size_t solutionB(string filename)
{
  Room a(filename);
  auto b = step(a);
  while(not (a==b))
    {
      a=b;
      b=step(a);
    }
  return a.count('#');
}
