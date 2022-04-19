#pragma once
#include<set>

using namespace std;

struct Range
{
  int min;
  int max;

  unsigned int size() const{return 1+max-min;}
  set<Range> splitBy(Range const & tr) //tr = toRemove
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
};

bool operator<(Range const &a, Range const &b);
