#include "solution_a.hh"

Solution& Solution::operator<<(std::string const &s)
{
  if(s.empty()) return *this;
      
  int repeat;
  char dir;
  std::istringstream in(s);
  in>>dir>>repeat;
  while(repeat-- > 0)
    visited.insert(step(dir));
  return *this;
}

int Solution::ans() const 
{
  return visited.size();
}

Coord SolutionA::step(char dir)
{
  return r.step(dir);
}
