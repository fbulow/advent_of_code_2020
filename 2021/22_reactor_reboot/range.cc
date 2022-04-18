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
