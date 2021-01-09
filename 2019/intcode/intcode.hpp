#include <map>
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
#include <sstream>
#include <queue>
using namespace std;
using I = long long int;

class IntCode;
ostream& operator<<(ostream &out, IntCode const &ic);

unsigned int mode(I index, I command);
unsigned int opcode(I command);

class IntCode
{
  friend ostream& operator<<(ostream &out, IntCode const &ic);
  int instructionPointer;
  map<I, I> memory;
  
public:
  int relativeBase{0};
  queue<I> input;
  queue<I> output;
  IntCode(string const &s, I pos=0)
    :IntCode(istringstream(s), pos)
  {}
  
  IntCode(istream &&in, I pos=0)
    :instructionPointer(pos)
  {
    I address=0;
    I i;
    in>>i;
    memory.insert({address++, i});
    char c;
    in>>c>>i;
    while(not in.eof())
      {
        memory.insert({address++, i});
        assert(c==',');
        in>>c>>i;
      }
    memory.insert({address++, i});
  }

  I& operator[](I i)
  {
    return memory[i];
  }
  
  bool operator==(IntCode const &other)const
  {
    return (memory==other.memory) and (instructionPointer==other.instructionPointer);
  }
  
  I first(){return memory[0];}
  I last(){return memory.rbegin()->second;}
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
    else if(code==3)
      {
        memory[memory[instructionPointer+1]]=input.front();
        input.pop();
        instructionPointer += 2;
      }
    else if(code==4)
      {
        output.push(memory[memory[instructionPointer+1]]);
        instructionPointer += 2;
      }
    else
      assert(false);
    return true;
    
  }
};


