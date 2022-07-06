#include "solution_a.hh"
#include "state.hpp"
#include <iostream>
#include <set>
bool solutionA(auto it, auto iend, auto blackListIter, State s)
{
  if(it==iend)
    return s.z()==0;
  else if(blackListIter->contains(s.data()))
    return false;
  else
    {
      blackListIter->insert(s.data());
      while(not s.inputRequired())
	{
	  s.apply(*it);
	  it++;
	}
      for(int i : {1,2,3,4,5,6,7,8,9})
	{
	  State s2 = s;
	  s2.input(i);
	  if(solutionA(it, iend, std::next(blackListIter), s2))
	    {
	      std::cout<<i;
	      return true;
	    }
	}
      return false;
    }
}


std::string solutionA(vector<Instruction> const &i)
{
  array<std::set<std::array<Int, 4>>, 15> blackList;
  State s;
  auto it = i.cbegin();
  
  solutionA(it, i.cend(), blackList.begin(), s);
  
  return"";
}

