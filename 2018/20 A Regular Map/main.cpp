#include<string_view>
#include<algorithm>
#include<functional>

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


unsigned int minSteps(function<char ()> next, unsigned int count=0)
{
  switch (next())
    {
    case '^':
      return minSteps(next);
    case '$' :
    case ')' :
      return count;
    case '(':
      return count + minSteps(next);
    case '|':
      return min(count, minSteps(next));
    case 'E':
    case 'W':
    case 'S':
    case 'N':
      return minSteps(next, count+1);
    }
  assert(false);
}

unsigned int minSteps(string s)
{
  istringstream in(s);
  auto next = [&in]()
  {
    char ret;
    in>>ret;
    return ret;
  };
  return minSteps(next,0);
}

  
