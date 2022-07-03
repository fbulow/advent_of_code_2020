#include "enums.hh"
#include<cassert>

Command command(std::string const &s)
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
