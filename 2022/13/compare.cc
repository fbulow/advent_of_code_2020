#include "compare.hh"

Compare compare(Int lhs, Int rhs)
{
  if (lhs<rhs)
    return Compare::Right;
  else if (lhs==rhs)
    return Compare::Equal;
  else
    return Compare::Wrong;
}

Compare compare(Node const &lhs, Node const &rhs)
{
  if(lhs.isInteger() and rhs.isInteger())
    return compare(lhs.getInt(), rhs.getInt());
  else if ((not lhs.isInteger()) and (not rhs.isInteger()))
    {
      auto a = lhs.cbegin();
      auto b = rhs.cbegin();

      if(a==lhs.cend())
	return b==rhs.cend()?Compare::Equal : Compare::Right;
      else if (b==rhs.cend())
	return Compare::Wrong;
      auto ret = compare(*a, *b);

      while(ret == Compare::Equal)
	{
	  a++;
	  b++;
	  if(a==lhs.cend())
	    return b==rhs.cend()?Compare::Equal : Compare::Right;
	  else if (b==rhs.cend())
	    return Compare::Wrong;
	  ret = compare(*a, *b);
	}
      return ret;
    }
  else if (lhs.isInteger())
    return compare(lhs.asList(), rhs);
  else
    {
      return compare(lhs, rhs.asList());
    }
}
