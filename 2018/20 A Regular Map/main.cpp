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

template<class T>
unsigned int minSteps(T & begin, T  & end, unsigned int count)
{
  char head = *begin;
  begin++;
  switch (head)
    {
    case '^':
      return minSteps(begin, end, count);
    case '$' :
    case ')' :
      return count;
    case '(':
      return count + minSteps(begin, end, 0);
    case '|':
      return min(count, minSteps(begin, end, 0));
    case 'E':
    case 'W':
    case 'S':
    case 'N':
      return minSteps(begin, end, count+1);
    }
  assert(false);
}


unsigned int minSteps(string s)
{
  auto a = s.begin();
  auto b = s.end();
  return minSteps(a,b, 0);
}

