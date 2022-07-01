#include "instruction.hpp"
#include<cassert>
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
  std::string s;
  in>>s;
  i.cmd = Instruction::command( s );
  in>>s;
  assert(s.size()==1);
  i.a = *s.begin();
  if(Instruction::nArg(i.cmd)>1)
    {
      in>>s;
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
