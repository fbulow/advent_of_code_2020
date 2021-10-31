#include<string_view>
#include<algorithm>
using namespace std;

bool isBeginning(char c)
{
  switch(c)
    {
    case '(':
    case '^':
      return true;
    default:
      return false;
    }
}

bool isEnd(char c)
{
  switch(c)
    {
    case ')':
    case '$':
      return true;
    default:
      return false;
    }
}

bool isBranched(string_view s)
{
  return s.end() != find(s.begin(), s.end(), '|');
}

bool isMove(char c)
{
  return not ( isBeginning(c) or isEnd(c)) ;
}

unsigned int minSteps(string_view s)
{
  auto branch = find(s.begin(), s.end(), '|');
  
  if(branch == s.end())
    return count_if(s.begin(), s.end(), isMove);
  else
    return min(minSteps({s.begin(), branch}),
               minSteps({next(branch), s.end()}));
}
