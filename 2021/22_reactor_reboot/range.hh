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
      return {{0,0},{1,1}, {2,2}};
    else if(min<tr.min)
      return {{min,tr.min-1},{tr.min,max}};
    else if(max>tr.max)
      return {{0,0},{1,1}};
    else
      return {*this};
  }
};

bool operator<(Range const &a, Range const &b);
