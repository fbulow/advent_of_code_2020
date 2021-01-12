#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
#include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
#include <functional>
#include <boost/algorithm/string.hpp> 
#include <boost/algorithm/string/join.hpp>
#include "intcode.hpp"
#include "coord.hpp"

using Co = Coord<I>;
using Color = bool;
struct Hull 
{
  map<Co, Color> data;

  Color color(Co const &c)
  {
    return data[c];
  }
  void paint(Co const&c, Color color)
  {
    data[c] = color;
  }

  size_t countVisited() const
  {
    return data.size();
  }
  
};

struct Robot
{
  template<class T>
  Robot(T &&arg)
  :brain(forward<T>(arg))
  {}
  IntCode brain;

  Co pos{0,0};
  Co dir{-1,0};
  Hull hull;
  
  bool step()
  {
    auto s= [this](){ if (not brain.step()) throw std::exception();};
    try{
      brain.input.push(hull.color(pos));
      s();
      while(brain.output.empty())
        s();
      hull.paint(pos, brain.output.front());
      brain.output.pop();
      s();
      while(brain.output.empty())
        s();
      if(brain.output.front() == 0)
        dir=dir.antiClockwise();
      else
        dir=dir.clockwise();
      brain.output.pop();
      pos+=dir;
      return true;
    }
    catch(...)
      {
        return false;
      }
  }
  
};
  
template<class T>
auto solutionA(T &&x)
{
  Robot r(forward<T>(x));
  while(r.step())
    {}
  return r.hull.countVisited();
}
