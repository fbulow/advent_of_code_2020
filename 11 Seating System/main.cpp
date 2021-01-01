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

struct Coord
{
  size_t row{0};
  size_t column{0};
};

using Dir=Coord;

class Room
{
  int Nrows{0};
  int Ncolumns{0};
  vector<char> data;
public:
  Room(string filename)
  {
    ifstream in(filename);
    assert(in.is_open());
    string line;
    deque<string> tmp;
    assert(getline(in, line));
    assert(line.size()!=0);
    Ncolumns = line.size();
    tmp.push_back(line);
    
    while(getline(in, line))
      {
        if(not line.empty())
          {
            Nrows++;
            tmp.push_back(line);
          }
      }
    Nrows++;
    data.resize(Nrows*Ncolumns);
    auto it = data.begin();
    for(string &row: tmp)
      it = copy(row.begin(), row.end(), it);
  }

  unsigned int count(char c) const
  {
    return std::count(data.cbegin(),
                      data.cend(),
                      c);
  }

  
  char operator[](size_t i)
  {
    return data[i];
  }
  char& operator[](Coord const &c)
  {
    assert(c.row< Nrows);
    assert(c.column< Ncolumns);

    return data[c.row*Ncolumns + c.column];
  }

  char visible(Coord c, Dir d) const 
  {
    return '#';
  }
  
  unsigned int countVisible(Coord c, char state='#')
  {
    array<Coord,8> const directions({{0,1}, {0, -1},
                                     {1,0}, {-1, 0},
                                     {1,1}, {-1,1}, {1,-1}, {-1,-1}});

    
    return count_if(directions.cbegin(),
                    directions.cend(),
                    [this, c, state](Coord const &dir)
                    {
                      return visible(c, dir)==state;
                    });
    
  }
  
};

