#pragma once
#include<array>
#include"enums.hh"
using Int = long long int;

class Instruction;

class State
{
  std::array<Int, 4> s{0,0,0,0};
  int value(Storage s);
public:
  Int w() const {return s[0];}
  Int x() const {return s[1];}
  Int y() const {return s[2];}
  Int z() const {return s[3];}  

  void apply(Instruction const&);
};
