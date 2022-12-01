#include "PositiveIntOrEmpty.hh"
#include <cassert>
#include <sstream>

using namespace std;

PositiveIntOrEmpty::PositiveIntOrEmpty(string const & s)
{
  if(s.empty())
    value_=-1;
  else
    {
      istringstream in(s);
      in>>value_;
    }
}

int PositiveIntOrEmpty::value() const {
  assert(not empty());
  return value_;
}
