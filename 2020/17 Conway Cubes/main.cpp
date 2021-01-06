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

template<int N>
struct Coord
{
  array<int, N> data;

  int x() const {return data[0];}
  int y() const {return data[1];}
  int z() const {return data[2];}
  int w() const {return data[3];}

  Coord(initializer_list<int> const &x)
    :Coord(vector<int>(x))
  {}
  Coord(vector<int> x)
  {
    data.fill(0);
    copy(x.begin(), x.end(), data.begin());
  }

  bool operator!=(Coord<N> const &other) const
  {
    return data!=other.data;
  }
  bool operator==(Coord<N> const &other) const
  {
    return data==other.data;
  }
  bool operator<(Coord<N> const &other) const
  {
    return data<other.data;
  }

};





template<int N>
class Conway
{
  using CoordN = Coord<N>;
  set<CoordN> active;
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
            active.emplace(CoordN{row, (int) y});
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
    map<CoordN, Cell> heat;
    
    for(CoordN const &c : active)
      {
        heat[c].activate();
        for(auto d: adjecent(c))
          heat[d]++;
      }

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

  Conway<3> sut(filename);
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  
  return sut.countActive();
}

unsigned int solutionB(string filename)
{

  Conway<4> sut(filename);
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  sut.step();
  
  return sut.countActive();
}

void adjRec(auto retInsert, auto it, auto const& end)
{
  if(next(it)==end)
    {
      (*it)-=1;
      retInsert();
      (*it)+=2;
      retInsert();
      (*it)-=1;
      retInsert();
    }
  else
    {
      (*it)-=1;
      adjRec(retInsert, next(it), end);
      (*it)+=2;
      adjRec(retInsert, next(it), end);
      (*it)-=1;
      adjRec(retInsert, next(it), end);
    }
}

template<int N>
vector<Coord<N>> adjecent(Coord<N> const &c)
{
    
  vector<Coord<N>> ret;
  if constexpr (N==3)
     ret.reserve(27);

  Coord<N> tmp(c);

  auto retInsert = [&ret, &c, &tmp]()
  {
    if(tmp!=c)
      ret.push_back(tmp);
  };
  
  auto &d=tmp.data;

  adjRec(retInsert, d.begin(), d.end());
  
  return ret;
}
