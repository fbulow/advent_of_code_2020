#include "range.hh"
bool operator<(Range const &a, Range const &b)  
{
  if(a.min<b.min)
    return true;
  if(a.min>b.min)
    return false;
  else
    return a.max<b.max;
}

set<Range> Range::splitBy(Range const & tr) const
  {

    if((max>tr.max) and (min<tr.min))
      return {{min,tr.min-1},tr, {tr.max+1,max}};
    else if(min<tr.min)
      return {{min,tr.min-1},{tr.min,max}};
    else if(max>tr.max)
      return {{min,tr.max},{tr.max+1,max}};
    else
      return {*this};
  }
