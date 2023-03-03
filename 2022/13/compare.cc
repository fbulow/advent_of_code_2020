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

Compare compare(auto const &abeg,
		auto const &aend,
		auto const &bbeg,
		auto const &bend)
{
  if(abeg==aend)
    return bbeg==bend?Compare::Equal : Compare::Right;
  else if (bbeg==bend)
    return Compare::Wrong;
  else
    {
      auto ret = compare(*abeg, *bbeg);
      if( ret != Compare::Equal)
	return ret;
      else
	return compare(next(abeg), aend,
		       next(bbeg), bend);
    }
}


Compare compare(Node const &lhs, Node const &rhs)
{
  if(lhs.isInteger() and rhs.isInteger())
    return compare(lhs.getInt(), rhs.getInt());
  else if ((not lhs.isInteger()) and (not rhs.isInteger()))
    {
      return compare(lhs.cbegin(),
		     lhs.cend(),
		     rhs.cbegin(),
		     rhs.cend());
    }
  else if (lhs.isInteger())
    return compare(lhs.asList(), rhs);
  else
    {
      return compare(lhs, rhs.asList());
    }
}
