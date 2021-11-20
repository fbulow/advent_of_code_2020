#include "operations.hh"
#include <gtest/gtest.h>
#include <cassert>

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

int& Registers::operator[](size_t x)
{
  assert(x<data.size());
  return data[x];
}
  
bool Registers::operator==(Registers const& other) const
{
  if(data.size()!=other.data.size())
    return false;
  for(size_t i =0; i< data.size();i++)
    if(data[i]!=other.data[i])
      return false;
  return true;
}



// Addition:

//     addr (add register) stores into register C the result of adding register A and register B.
Registers& Registers::addr(int a, int b, int c)
{
  data[c]=data[a]+data[b];
  return *this;
}
  
//     addi (add immediate) stores into register C the result of adding register A and value B.
Registers& Registers::addi(int a, int b, int c)
{
  data[c]=data[a]+b;
  return *this;
}

// Multiplication:

//     mulr (multiply register) stores into register C the result of multiplying register A and register B.
Registers& Registers::mulr(int a, int b, int c)
{
  data[c]=data[a]*data[b];
  return *this;
}
  
//     muli (multiply immediate) stores into register C the result of multiplying register A and value B.
Registers& Registers::muli(int a, int b, int c)
{
  data[c]=data[a]*b;
  return *this;
}

// Bitwise AND:

//     banr (bitwise AND register) stores into register C the result of the bitwise AND of register A and register B.
Registers& Registers::banr(int a, int b, int c)
{
  data[c]=data[a]&data[b];
  return *this;
}

  
//     bani (bitwise AND immediate) stores into register C the result of the bitwise AND of register A and value B.
Registers& Registers::bani(int a, int b, int c)
{
  data[c]=data[a]&b;
  return *this;
}

  
// Bitwise OR:

//     borr (bitwise OR register) stores into register C the result of the bitwise OR of register A and register B.
Registers& Registers::borr(int a, int b, int c)
{
  data[c]=data[a]|data[b];
  return *this;
}

//     bori (bitwise OR immediate) stores into register C the result of the bitwise OR of register A and value B.
Registers& Registers::bori(int a, int b, int c)
{
  data[c]=data[a]|b;
  return *this;
}

// Assignment:

//     setr (set register) copies the contents of register A into register C. (Input B is ignored.)
Registers& Registers::setr(int a, int b, int c)
{
  data[c]=data[a];
  return *this;
}
//     seti (set immediate) stores value A into register C. (Input B is ignored.)
Registers& Registers::seti(int a, int b, int c)
{
  data[c]=a;
  return *this;
}


// Greater-than testing:

//     gtir (greater-than immediate/register) sets register C to 1 if value A is greater than register B. Otherwise, register C is set to 0.
Registers& Registers::gtir(int a, int b, int c)
{
  data[c] = a>data[b] ? 1: 0;
  return *this;
}
  
//     gtri (greater-than register/immediate) sets register C to 1 if register A is greater than value B. Otherwise, register C is set to 0.
Registers& Registers::gtri(int a, int b, int c)
{
  data[c] = data[a]>b ? 1: 0;
  return *this;
}

//     gtrr (greater-than register/register) sets register C to 1 if register A is greater than register B. Otherwise, register C is set to 0.
Registers& Registers::gtrr(int a, int b, int c)
{
  data[c] = data[a]>data[b] ? 1: 0;
  return *this;
}

// Equality testing:

//     eqir (equal immediate/register) sets register C to 1 if value A is equal to register B. Otherwise, register C is set to 0.
Registers& Registers::eqir(int a, int b, int c)
{
  data[c] = a==data[b] ? 1: 0;
  return *this;
}
  
//     eqri (equal register/immediate) sets register C to 1 if register A is equal to value B. Otherwise, register C is set to 0.
Registers& Registers::eqri(int a, int b, int c)
{
  data[c] = data[a]==b ? 1: 0;
  return *this;
}

//     eqrr (equal register/register) sets register C to 1 if register A is equal to register B. Otherwise, register C is set to 0.
Registers& Registers::eqrr(int a, int b, int c)
{
  data[c] = data[a]==data[b] ? 1: 0;
  return *this;
}

unsigned int possible(Registers const & input,                      
                      int a, int b, int c,
                      Registers const & result)
{
  return 0
    + (result == Registers(input).addr(a, b, c)? 1 : 0 )
    + (result == Registers(input).addi(a, b, c)? 1 : 0 )
    + (result == Registers(input).mulr(a, b, c)? 1 : 0 )
    + (result == Registers(input).muli(a, b, c)? 1 : 0 )
    + (result == Registers(input).banr(a, b, c)? 1 : 0 )
    + (result == Registers(input).bani(a, b, c)? 1 : 0 )
    + (result == Registers(input).borr(a, b, c)? 1 : 0 )
    + (result == Registers(input).bori(a, b, c)? 1 : 0 )
    + (result == Registers(input).setr(a, b, c)? 1 : 0 )
    + (result == Registers(input).seti(a, b, c)? 1 : 0 )
    + (result == Registers(input).gtir(a, b, c)? 1 : 0 )
    + (result == Registers(input).gtri(a, b, c)? 1 : 0 )
    + (result == Registers(input).gtrr(a, b, c)? 1 : 0 )
    + (result == Registers(input).eqir(a, b, c)? 1 : 0 )
    + (result == Registers(input).eqri(a, b, c)? 1 : 0 )
    + (result == Registers(input).eqrr(a, b, c)? 1 : 0 );
}

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

  EXPECT_EQ(3, possible(Registers(3, 2, 1, 1),
                        2, 1, 2,
                        Registers(3, 2, 2, 1)
                        ));
                        
  
}

struct InputParser;
istream& operator>>(istream&, InputParser&);

InputParser::InputParser(istream& in)
{
  in>>*this;
}

unsigned int InputParser::possible() const
{
  return ::possible(before, a,b,c, after);
}


istream& operator>>(istream& in, InputParser &x)
{
  int optcode;
  string word;
  char c;
  in>> word;
  if(in.eof())
    return in;
  if(not in.good()) return in;
  assert(word == "Before:");
  assert(in.get() == ' ');
  assert(in.get() == '[');
  in
    >> x.before[0]
    >> c ;
  assert(c==',');
  in>>x.before[1]>> c;

  assert(c==',');
  in>>x.before[2] >> c;
  
  assert(c==',');
  in>>x.before[3]>>c;
  assert(c==']');
  
  in>>optcode >>x.a >> x.b >> x.c;

  in>> word >>c;
  assert(word == "After:");
  assert(c == '[');
  in
    >> x.after[0]
    >> c ;
  assert(c==',');
  in>>x.after[1]>> c;

  assert(c==',');
  in>>x.after[2] >> c;
  
  assert(c==',');
  in>>x.after[3]>>c;
  assert(c==']');

  
  return in;
}

TEST(InputParser, example)
{
  istringstream in(
                   "Before: [1, 2, 3, 4]\n"
                   "5 6 7 8\n"
                   "After:  [9, 10, 11, 12]\n"
                   "\n"
                   "Before: [2, 0, 0, 1]\n"
                   "15 3 1 3\n"
                   "After:  [2, 0, 0, 1]\n"
                   );

  InputParser sut(in);
  EXPECT_EQ(Registers(1, 2, 3, 4),
            sut.before);

  EXPECT_EQ(6,
            sut.a);
  EXPECT_EQ(7,
            sut.b);
  EXPECT_EQ(8,
            sut.c);

  EXPECT_EQ(Registers(9, 10, 11, 12),
            sut.after);

  in>>sut;

  EXPECT_EQ(Registers(2, 0, 0, 1),
            sut.before);

  EXPECT_EQ(3,
            sut.a);
  EXPECT_EQ(1,
            sut.b);
  EXPECT_EQ(3,
            sut.c);

  EXPECT_EQ(Registers(2, 0, 0, 1),
            sut.after);

  EXPECT_FALSE(in.eof());
  in>> sut;
  EXPECT_TRUE(in.eof());

}
  
