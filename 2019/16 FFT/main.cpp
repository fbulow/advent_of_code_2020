#include <vector>
#include <array>
#include <numeric>
#include "cycle.hpp"
#include "summation.hpp"
#include <iostream>
#include <algorithm>
#include <execution> 
using namespace std;


int keep_one_digit(int sum)
{
  if(sum<0)
    return keep_one_digit(-sum);
  else
    return sum%10;
}


class Pattern
{
  vector<int> pattern;
  unsigned int repeat;
  unsigned int counter{0};
public:
  Pattern(vector<int> pattern, unsigned int repeat)
    :pattern(move(pattern))
    ,repeat(repeat)
  {}
    
  int operator()()
  {
    counter=(counter+1)%(repeat*pattern.size());
    return pattern[counter/repeat];
  }
};

vector<int> signal(string_view s)
{
  vector<int> ret;
  ret.reserve(s.size());
  for(char c:s)
    ret.push_back(c-'0');
  return ret;
}

void phase(Summation const &sum,
           vector<int> pattern,
           vector<int> &ret
           )
{
  for(unsigned int i = 0; i < ret.size() ;i++)
    ret[i]=i;
  for_each(std::execution::par,
           ret.begin(),
           ret.end(),
           [sum](auto &&ret)
           {
             auto stride = ret+1;
             ret = 0;
             for(unsigned int segment=1;segment<sum.size(stride);segment+=2)
               ret+=cycle(segment)*sum(segment,stride);
             ret=keep_one_digit(ret);
           });
  cout<<endl;
}

vector<int>  phase(vector<int> signal,
                   vector<int> pattern,
                   unsigned int iterations=1)
{
  vector<int> ret;
  ret.resize(signal.size());

  while(iterations-->0)
    {
      cout<<iterations;
      phase({signal}, pattern, ret);
      swap(signal,ret);
    }
  return signal;
}

vector<int>  phase(string_view const &signal,
                   vector<int> pattern,
                   unsigned int iterations=1)
{return phase(::signal(signal), pattern, iterations);}

vector<int> solutionA(string input)
{
  auto ret = phase(input,
                   vector<int>{0, 1, 0, -1},
                   100);

  return {ret.begin(),
    next(ret.begin(), 8)};
}

