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
#include <boost/algorithm/string/join.hpp>

using namespace std;
using I = long int;

class IntCode
{
  friend ostream& operator<<(ostream &out, IntCode const &ic);
  int position;
  vector<I> data;

public:
  IntCode(string const &s, I pos=0)
    :IntCode(istringstream(s), pos)
  {}
  
  IntCode(istream &&in, I pos=0)
    :position(pos)
  {
    I i;
    in>>i;
    data.push_back(i);
    char c;
    in>>c>>i;
    while(not in.eof())
      {
        data.push_back(i);
        assert(c==',');
        in>>c>>i;
      }
    data.push_back(i);
  }

  I& operator[](int i)
  {
    return data[i];
  }
  
  bool operator==(IntCode const &other)const
  {
    return (data==other.data) and (position==other.position);
  }
  
  I first() const {return data[0];}
  I last() const {return *data.rbegin();}
  bool step()
  {
    auto code = data[position];
    if(code==99)
      return false;
    else if(code==1)
      {
        data[data[position+3]] = data[data[position+1]] + data[data[position+2]];
        position += 4;
      }
    else if(code==2)
      {
        data[data[position+3]] = data[data[position+1]] * data[data[position+2]];
        position += 4;
      }
    else
      assert(false);
    return true;
    
  }
};

ostream& operator<<(ostream &out, IntCode const &ic)
{
  out<<ic.data[0];
  for_each(next(ic.data.begin()), ic.data.end(),
           [&out](I i){
             out<<","<<i;
           });
  return out;
}


I solutionA(string filename)
{
  IntCode s((ifstream(filename)));
  s[1]=12;
  s[2]=2;
  while(s.step())
    {}
  return s.first();
}
