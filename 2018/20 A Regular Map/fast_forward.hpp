#pragma once
#include <algorithm>
#include <cassert>
using namespace std;

template<class T>
T to_closing(T it, T end)
{
  int count=1;
  assert(*it=='|');
  return find_if(it, end,
                 [ &count ](char c)
                 {
                   if(c=='(')
                     count++;
                   else if (c==')')
                     count--;
                   return count==0;
                 });
}

template<class T>
T to_closing_or_branch(T it, T end)
{
  assert(*it=='(' or *it=='|');
  int count=1;
  auto ret = find_if(next(it), end,
                     [ &count ](char c)
                     {
                       if(c=='(')
                         count++;
                       else if (c==')')
                         {
                           count--;
                           assert(count>=0);
                         }
                       else if (count==1 and c=='|')
                         return true;
                       return count==0;
                     });
  assert(*ret==')' or *ret=='|');
  return ret;
}

