#pragma once
#include<string>
#include<vector>

using namespace std;

using Arg = char;

class Instruction{

public:
  enum class Command {inp, add, mul, div, mod, eql} cmd;
  Arg a{'\0'};
  Arg b{'\0'};
  
  
  static Command command(string const&);
  static unsigned int nArg(Command c);
};


istream& operator>>(istream& in, Instruction &i);
istream& operator>>(istream& in, vector<Instruction> &v);
