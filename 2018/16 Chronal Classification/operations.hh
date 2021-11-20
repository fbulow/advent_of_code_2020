#pragma once
#include <array>
#include <iostream>

using namespace std;
class Registers{
  array<int, 4> data;
public:
  template<class ... ARG>
  Registers(ARG...arg)
    :data{arg...}
  {}

  int& operator[](size_t x);
  bool operator==(Registers const& other) const;
  friend ostream& operator<<(ostream &out, Registers const & r);

  Registers& addr(int a, int b, int c);
  Registers& addi(int a, int b, int c);
  Registers& mulr(int a, int b, int c);
  Registers& muli(int a, int b, int c);
  Registers& banr(int a, int b, int c);
  Registers& bani(int a, int b, int c);
  Registers& borr(int a, int b, int c);
  Registers& bori(int a, int b, int c);
  Registers& setr(int a, int b, int c);
  Registers& seti(int a, int b, int c);
  Registers& gtir(int a, int b, int c);
  Registers& gtri(int a, int b, int c);
  Registers& gtrr(int a, int b, int c);
  Registers& eqir(int a, int b, int c);
  Registers& eqri(int a, int b, int c);
  Registers& eqrr(int a, int b, int c);
};


struct InputParser
{
  Registers before;
  int a{0};
  int b{0};
  int c{0};
  Registers after;
  
  InputParser(istream& in);
  unsigned int possible() const;
  
};

istream& operator>>(istream&, InputParser&);
