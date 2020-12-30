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
#include <initializer_list>
#include <functional>
using namespace std;

using I = unsigned long int;

I score(auto &x)
{
  assert(not x.empty());
  I factor =1;
  return accumulate(x.rbegin(),
                    x.rend(),
                    I{0},
                    [&factor](I sum, I value)
                    {
                      return sum+(factor++)*value;
                    });
}
struct Game;
ostream& operator<<(ostream& ret, Game const &g);

struct Game
{
  list<I> one;
  list<I> two;

  Game() = default;
  Game(string filename)
  {
    ifstream cin(filename);
    assert(cin.is_open());
    string line;
    getline(cin, line);
    assert("line==Player 1:");
    getline(cin, line);
    while(not line.empty())
      {
        istringstream in(line);
        I value;
        in>>value;
        one.push_back(value);
        getline(cin, line);
      }

    getline(cin, line);
    assert("line==Player 2:");
    getline(cin, line);
    while(not line.empty())
      {
        istringstream in(line);
        I value;
        in>>value;
        two.push_back(value);
        getline(cin, line);
      }
  }
  Game(initializer_list<I> &&one,
       initializer_list<I> &&two)
    :one(move(one))
    ,two(move(two))
  {}


  void playRound()
  {
    assert(one.front() != two.front());
    if(one.front() > two.front())
      {
        one.push_back(one.front());
        one.push_back(two.front());
      }
    else //(two.front() > one.front())
      {
        two.push_back(two.front());
        two.push_back(one.front());
      }        
    one.pop_front();
    two.pop_front();
  }

  void finnish()
  {
    while((not one.empty()) and (not two.empty()))
      playRound();
  }

  I score()
  {
    finnish();
    if (one.empty())
      return ::score(two);
    else
      return ::score(one);
  }

  auto hash() const
  {
    ostringstream out;
    out<<*this;
    std::hash<string> h;
    return h(out.str());
  }
  
};

ostream& operator<<(ostream& ret, Game const &g)
{
  ret<<"Player 1:";
  for(auto x:g.one)
    ret<<" "<<x;
  ret<<endl<<"Player 2:";
  for(auto x:g.two)
    ret<<" "<<x;
  ret<<endl;
  return ret;
}


I solutionA(string filename)
{
  return Game(filename).score();
}
