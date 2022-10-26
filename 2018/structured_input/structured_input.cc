#include "structured_input.hh"
#include <cstdio>
namespace{
  void compareFirst(istream& real, istream& chunk)
  {
    if(real.eof()) return;
    
    char aa;
    aa = chunk.get();
    if(chunk.eof()) return;

    char bb;
    bb = real.get();
    if(aa!=bb)
      throw Missmatch(aa, bb);
    try
      {
	compareFirst(real, chunk);
      }
    catch(Missmatch &m)
      {
	m.expected_+=aa;
	m.got_+=aa;
      
	throw m;
      }
  }
}

istream& operator>>(istream& in, const string &s)
{
  try
    {
      istringstream ins(s);
      compareFirst(in, ins);
    }
  catch(Missmatch const &m)
    {
      if (not in.eof())
	throw m;
    }
  return in;
}


