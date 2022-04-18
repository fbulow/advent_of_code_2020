#pragma once

struct Range
{
  int min;
  int max;

  unsigned int size() const{return 1+max-min;}
};
