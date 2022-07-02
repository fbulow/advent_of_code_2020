#include "instruction.hpp"
#include<cassert>
#include<iostream>

using namespace std;

Instruction::Command Instruction::command(string const&s)
{
  if(s=="inp")
    return Command::inp;
  else if(s=="add")
    return Command::add;
  else if(s=="mul")
    return Command::mul;
  else if(s=="eql")
    return Command::eql;
  else if(s=="div")
    return Command::div;
  else if(s=="mod")
    return Command::mod;

  assert(false);
  return {};
}

istream& operator>>(istream& in, Instruction &i)
{
  if(in.eof())
    return in;
  std::string s;
  in>>s;
  if(in.eof())
    return in;
  i.cmd = Instruction::command( s );
  in>>s;
  assert(s.size()==1);
  i.a = *s.begin();
  if(Instruction::nArg(i.cmd)>1)
    {
      assert(not in.eof());
      in>>s;
      assert(s.size()==1);
      i.b = *s.begin();
    }
  
  return in;
}

unsigned int Instruction::nArg(Command c)
{
  if (c==Command::inp)
    return 1;
  else
    return 2;
}

istream& operator>>(istream& in, vector<Instruction> &v)
{
  Instruction i;
  while(not in.eof())
    {
      in>>i;
      if(not in.fail())
	v.push_back(i);
    }
  return in;
}

