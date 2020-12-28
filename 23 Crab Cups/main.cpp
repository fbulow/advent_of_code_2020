#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
using namespace std;

class Cups;
ostream& operator<<(ostream& cout, Cups const & c);

char nextDown(char c)
{
  if(c=='1') return '9';
  return c-1;
}

class Cups{
  list<char> s;
public:
  Cups(string const &s)
    :s(s.begin(), s.end())
  {}
  string toString() const {return {s.begin(), s.end()};}
  void shiftRight(unsigned int times = 1)
  {
    while(times>0)
      {
        s.push_front(s.back());
        s.pop_back();
        times--;
      }
  }
  void placePickupLast()
  {
    shiftRight(5);
  }
  auto stashBeginConst() const
  {
    return next(s.begin(), 6);
  }
  auto stashBegin()
  {
    return next(s.begin(), 6);
  }
  auto stashEndConst() const
  {
    return s.end();
  }
  
  char destination() const
  {
    char selectedOne = nextDown(*next(s.begin(),5));
    
    while (stashEndConst() != find(stashBeginConst(),
                              stashEndConst(),
                              selectedOne))
      selectedOne = nextDown(selectedOne);
    return selectedOne;
  }
  char beforeStash() const
  {
    return *prev(stashBeginConst());
  }
  
  void smallShiftLeft()
  {
    auto tail = s.begin();
    auto head = next(tail);

    while(head != stashBegin())
      {
        swap(*head, *tail);
        head = next(head);
        tail = next(tail);
      }
  }

  void smallShiftUntilLastIs(char v)
  {
    while(beforeStash()!=v)
      smallShiftLeft();
  }

  void shiftUntilFirstOneIs(char v)
  {
    while(*s.begin()!=v)
      shiftRight();    
  }

  void makeMove()
  {
    char selected = *s.begin();
    placePickupLast();
    smallShiftUntilLastIs(destination());
    auto selectedIt = find(s.begin(),
                           s.end(),
                           selected);

    char nextSelected;
    if(selectedIt==s.end())
      nextSelected=*s.begin();
    else
      nextSelected=*next(selectedIt);
    shiftUntilFirstOneIs(nextSelected);
  }

  string solveA()
  {
    for(auto i=0;i<100;i++)
      makeMove();
    shiftUntilFirstOneIs('1');
    return toString().substr(1);
  }
  
};

ostream& operator<<(ostream& cout, Cups const & c)
{
  cout<<c.toString()<<endl;
  return cout;
}

#include"quickCups.cpp"
