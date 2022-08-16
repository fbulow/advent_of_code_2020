#pragma once
#include<limits>
#include<iostream>
class Result{
  using Base = int;
  Base data;
  friend Result operator+(Result a, Result const & b);
  friend Result operator+=(Result & a, Result const & b);
  friend bool operator<(Result const & a, Result const & b);
  friend void PrintTo(Result const &r, std::ostream *os);
public:
  Result()
    :data(std::numeric_limits<Base>::max())
  {}
  
  Result(auto x)
    :data(x)
  {}
  operator bool () const
  {
    return data!=std::numeric_limits<Base>::max();
  }
  operator Base const &() const
  {
    return data;
  }
};

inline
Result operator+=(Result & a, Result const & b)
{
  if(a and b)
    {
      a.data+=b.data;
      return a;
    }
  else
    return {};
}

inline
Result operator+(Result a, Result const & b)
{
  a+=b;
  return a;
}

inline
bool operator<(Result const & a, Result const & b)
{
  return a.data < b.data;
}

