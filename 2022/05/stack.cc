#include "stack.hh"
#include <cassert>

char Stack::top() const
{return data.empty()?' ':data.back();}

Stack& Stack::push_bottom(char c)
{
  data.insert(data.begin(),c);
  return *this;
}

Stack& Stack::push_top(char c)
{
  assert(c!=' ');
  data.push_back(c);
  return *this;
}

char Stack::pop()
{
  auto ret=top();
  assert(ret!=' ');
  data.pop_back();
  return ret;
}
