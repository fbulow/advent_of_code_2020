#pragma once
#include<vector>

using namespace std;

struct Range
{
  int min;
  int max;

  unsigned int size() const{return 1+max-min;}
  vector<Range> splitBy(Range const & tr) //tr = toRemove
  {
    Range r{0,0};

    if((max>tr.max) and (min<tr.min))
      return {r,r,r};
    else if(min<tr.min)
      return {r,r};
    else if(max>tr.max)
      return {r,r};
    else
      return {r};
  }
};

bool operator<(Range const &a, Range const &b);
