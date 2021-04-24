#include<vector>
#include<array>
#include <numeric> 
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

vector<int>  phase(vector<int> const &signal,
                   vector<int> pattern,
                   unsigned int iterations=1)
{
  vector<int> ret;
  ret.resize(signal.size());
  for(unsigned int i = 0; i < ret.size() ;i++)
    {
      ret[i] = keep_one_digit(
                              accumulate(signal.begin(),
                                         signal.end(),
                                         0,
                                         [ p = Pattern (pattern, i+1)]
                                         (auto left,
                                          auto right)
                                         mutable
                                         {
                                           return left+p()*right;
                                         })
                              );
    }
  if(iterations==0)
    return signal;
  else
    return phase(ret, pattern, iterations-1);
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
