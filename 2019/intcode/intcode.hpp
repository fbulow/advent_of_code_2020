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
#include <algorithm>
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
  I& ref(I index, I command)
  {
    switch(mode(index,command))
      {
      case 0://position mode
        return memory[memory[instructionPointer+index]];
      case 1:
        return memory[instructionPointer+index];
      case 2:
        return memory[relativeBase+memory[instructionPointer+index]];
      default:
        assert(false);
      }
  }
  
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

  void run()
  {
    while(step())
      {};
  }
  
  bool step()
  {
    auto inst = memory[instructionPointer];
    auto code = opcode(inst);
    I increase = 1;
    auto x = [this, inst, &increase](I index) -> I&
    {
      increase = max(increase, index+1);
      return ref(index, inst);
    };
      
    if(code==99)
      return false;
    else if(code==1)
      x(3) = x(1) + x(2);
    else if(code==2)
      x(3) = x(1) * x(2);
    else if(code==3)
      {
        x(1)=input.front();
        input.pop();
      }
    else if(code==4)
        output.push(x(1));
    else if(code==5) //Opcode 5 is jump-if-true: if the first
                     //parameter is non-zero, it sets the instruction
                     //pointer to the value from the second
                     //parameter. Otherwise, it does nothing.
      {
        if(x(1)!=0)
          {
            instructionPointer=x(2);
            return true;
          }
        x(2);
      }
    else if(code==6) //Opcode 6 is jump-if-false: if the first
                     //parameter is zero, it sets the instruction
                     //pointer to the value from the second
                     //parameter. Otherwise, it does nothing.
      {
        if(x(1)==0)
          {
            instructionPointer=x(2);
            return true;
          }
        x(2);
      }
    else if(code==7) //Opcode 7 is less than: if the first parameter
                     //is less than the second parameter, it stores 1
                     //in the position given by the third
                     //parameter. Otherwise, it stores 0.
      x(3) = ( x(1) < x(2) ) ? 1 : 0;
    else if(code==8) //Opcode 8 is equals: if the first parameter is
                     //equal to the second parameter, it stores 1 in
                     //the position given by the third
                     //parameter. Otherwise, it stores 0.
      x(3) = ( x(1) == x(2) ) ? 1 : 0;
    else if (code==9) //Opcode 9 adjusts the relative base by the
                      //value of its only parameter. The relative base
                      //increases (or decreases, if the value is
                      //negative) by the value of the parameter.
      relativeBase += x(1);
    else
      assert(false);

    instructionPointer += increase;
    return true;
  }
};


