#include <gtest/gtest.h>
#include <array>
#include <iostream>
using namespace std;
class Instruction 
{
  array<int, 4> data;
  public:
  template<class ... ARG>
  Instruction(ARG...arg)
    :data{arg...}
  {}
};

class Registers{
  array<int, 4> data;
public:
  template<class ... ARG>
  Registers(ARG...arg)
    :data{arg...}
  {}
  bool operator==(Registers const& other) const
  {
    if(data.size()!=other.data.size())
      return false;
    for(size_t i =0; i< data.size();i++)
      if(data[i]!=other.data[i])
        return false;
    return true;
  }
  Registers& operator<<(Instruction const & i)
  {
    return *this;
  }
  friend ostream& operator<<(ostream &out, Registers const & r);

  Registers& mulr(int a, int b, int c)
  {
    data[c]=data[a]*data[b];
    return *this;
  }
  Registers& addi(int a, int b, int c)
  {
    data[c]=data[a]+b;
    return *this;
  }
  Registers& seti(int a, int b, int c)
  {
    data[c]=a;
    return *this;
  }
  
};

ostream& operator<<(ostream &os, Registers const & r)
{
  bool first{true};
  os<<"(Register:";
  for(auto x: r.data)
    {
      if(first)
        os<<" ";
      else
        os<<", ";
      os <<x;
      first=false;
    }
  os<<")";
  return os;
}


TEST(registers, example)
{

// Before: [3, 2, 1, 1]
// 9 2 1 2
// After:  [3, 2, 2, 1]

  //    Opcode 9 could be mulr: register 2 (which has a value of 1) times register 1 (which has a value of 2) produces 2, which matches the value stored in the output register, register 2.
  EXPECT_EQ(Registers(3, 2, 2, 1),
            Registers(3, 2, 1, 1).mulr(2, 1, 2));

  //    Opcode 9 could be addi: register 2 (which has a value of 1) plus value 1 produces 2, which matches the value stored in the output register, register 2.
  EXPECT_EQ(Registers(3, 2, 2, 1),
            Registers(3, 2, 1, 1).addi(2, 1, 2));

  //    Opcode 9 could be seti: value 2 matches the value stored in the output register, register 2; the number given for B is irrelevant.
  EXPECT_EQ(Registers(3, 2, 2, 1),
            Registers(3, 2, 1, 1).seti(2, 1, 2));
  
}
