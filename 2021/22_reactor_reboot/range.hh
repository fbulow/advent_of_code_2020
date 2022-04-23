#pragma once
#include<set>

using namespace std;

struct Range
{
  int min;
  int max;

  long long  size() const{return 1+max-min;}
  set<Range> splitBy(Range const & tr) const;
  bool contains(int c) const {return (c>=min)and(c<=max);}
  int centre() const { return (min+max)/2; }
};

bool operator<(Range const &a, Range const &b);
