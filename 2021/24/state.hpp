#pragma once
#include<array>
#include"enums.hh"
#include<optional>

using Int = long long int;

class Instruction;
using Arg=char;

class State
{
  std::array<Int, 4> s{0,0,0,0};
  Arg inputTarget='\0';
public:
  Int w() const {return s[0];}
  Int x() const {return s[1];}
  Int y() const {return s[2];}
  Int z() const {return s[3];}  

  void apply(Instruction const&);
  void input(int);
  bool inputRequired() const {return inputTarget!='\0';}

private:
  Int value(Arg) const;
};
