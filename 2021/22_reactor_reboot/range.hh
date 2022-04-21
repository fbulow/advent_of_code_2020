#pragma once
#include<set>

using namespace std;

struct Range
{
  int min;
  int max;

  unsigned int size() const{return 1+max-min;}
  set<Range> splitBy(Range const & tr);
};

bool operator<(Range const &a, Range const &b);
