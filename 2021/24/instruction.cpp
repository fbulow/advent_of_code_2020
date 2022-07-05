#include "instruction.hpp"
#include<cassert>
#include<iostream>

using namespace std;


istream& operator>>(istream& in, Instruction &i)
{
  if(in.eof())
    return in;
  std::string s;
  in>>s;
  if(in.eof())
    return in;
  else if(s.empty())
    {
      in.setstate(std::ios::eofbit);
      assert(in.eof());
      return in;
    }

  i.cmd = command( s );
  in>>s;
  assert(s.size()==1);
  i.a = *s.begin();
  if(Instruction::nArg(i.cmd)>1)
    {
      assert(not in.eof());
      char c = in.peek();
      while(' ' == in.peek())
	in>>c;
      c = in.peek();
      if((c>='w') and (c<='z'))
	{
	  in>>s;
	  assert(s.size()==1);
	  i.b = *s.begin();
	}
      else
	{
	  Int nxt;
	  in>>nxt;
	  i.b={nxt};
	}
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

