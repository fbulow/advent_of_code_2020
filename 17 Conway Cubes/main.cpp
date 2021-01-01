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



class Cell{
  bool wasActive;
  int activeNeighbors;
public:
  Cell(bool active = false, int activeNeighbors=0)
    :wasActive{active}
    ,activeNeighbors(activeNeighbors)
  {}
  int count() const
  {
    return activeNeighbors;
  }
  Cell& operator++(int)
  {
    activeNeighbors++;
    return *this;
  }

  void activate(){wasActive=true;};
  
  bool becomesActive() const
  {
    if(wasActive)
      //If a cube is active and exactly 2 or 3 of its neighbors are also
      //active, the cube remains active. Otherwise, the cube becomes
      //inactive.
      return
        (activeNeighbors == 2) or
        (activeNeighbors == 3);
    else
      //If a cube is inactive but exactly 3 of its neighbors are active,
      //the cube becomes active. Otherwise, the cube remains inactive.
      return activeNeighbors == 3;
  }
};

struct Coord{
  int x;
  int y;
  int z;
};

bool operator<(Coord const &a, Coord const &b)
{
  if(a.x!=b.x)
    return a.x<b.x;
  else if(a.y!=b.y)
    return a.y<b.y;
  else if(a.z!=b.z)
    return a.z<b.z;
  else // is equal
    return false;
}


class Conway
{
  set<Coord> active;
  //  map<Coord, Cell> heatMap;
public:
  Conway(initializer_list<string> input)
    :Conway(deque<string>(input))
  {}

  Conway(string filename)
    :Conway([filename](){
      ifstream in(filename);
      assert(in.is_open());
      string line;
      deque<string> data;
      while(getline(in, line))
        data.push_back(line);
      return data;
    }())
  {}
  
  Conway(deque<string> input)
  {
    int row = -1;
    for(string s:input)
      {
        row++;
        auto y = s.find('#');
        while(y!=string::npos)
          {
            active.emplace(Coord{row, (int) y, 0});
            y = s.find('#', y+1);
          }
        
      }
  }
  unsigned int countActive() const
  {
    return active.size();
  }
  void step()
  {
    map<Coord, Cell> heat;
    for(Coord const &c : active)
      for(int dx=-1; dx<2; dx++)
        for(int dy=-1; dy<2; dy++)
          for(int dz=-1; dz<2; dz++)
            if((dx==dy) and (dy==dz) and (dz==0))
              heat[c].activate();
            else
              heat[Coord{c.x+dx, c.y+dy, c.z+dz}]++;

    active.clear();

    for(auto& [coord, cell] : heat)
      {
        if(cell.becomesActive())
          active.insert(coord);
      }
  }
};


unsigned int solutionA(string filename)
{

  Conway sut(filename);
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  
  return sut.countActive();
}
