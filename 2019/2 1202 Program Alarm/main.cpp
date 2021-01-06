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
  int instructionPointer;
  vector<I> memory;

public:
  IntCode(string const &s, I pos=0)
    :IntCode(istringstream(s), pos)
  {}
  
  IntCode(istream &&in, I pos=0)
    :instructionPointer(pos)
  {
    I i;
    in>>i;
    memory.push_back(i);
    char c;
    in>>c>>i;
    while(not in.eof())
      {
        memory.push_back(i);
        assert(c==',');
        in>>c>>i;
      }
    memory.push_back(i);
  }

  I& operator[](int i)
  {
    return memory[i];
  }
  
  bool operator==(IntCode const &other)const
  {
    return (memory==other.memory) and (instructionPointer==other.instructionPointer);
  }
  
  I first() const {return memory[0];}
  I last() const {return *memory.rbegin();}
  bool step()
  {
    auto code = memory[instructionPointer];
    if(code==99)
      return false;
    else if(code==1)
      {
        memory[memory[instructionPointer+3]] = memory[memory[instructionPointer+1]] + memory[memory[instructionPointer+2]];
        instructionPointer += 4;
      }
    else if(code==2)
      {
        memory[memory[instructionPointer+3]] = memory[memory[instructionPointer+1]] * memory[memory[instructionPointer+2]];
        instructionPointer += 4;
      }
    else
      assert(false);
    return true;
    
  }
};

ostream& operator<<(ostream &out, IntCode const &ic)
{
  out<<ic.memory[0];
  for_each(next(ic.memory.begin()), ic.memory.end(),
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
