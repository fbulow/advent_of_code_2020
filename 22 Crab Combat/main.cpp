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
  Game(list<I> &&one,
       list<I> &&two)
    :one(move(one))
    ,two(move(two))
  {}


  virtual void playRound()
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

  virtual void finnish()
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
  
};

ostream& operator<<(ostream& ret, Game const &g)
{
  ret<<endl<<"Player 1:";
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

struct Recursive: Game
{

  Recursive() = default;
  Recursive(string filename)
    :Game(filename)
  {}
  
  Recursive(list<I> &&one,
            list<I> &&two)
    :Game(move(one),
          move(two))
  {}

  size_t hash() const
  {
    ostringstream out;
    out<<*this;
    std::hash<string> h;
    return h(out.str());
  }

  static bool canPlayRecursive(list<I> deck)
  {
    return deck.size() >= 1+deck.front();
  }

  
  optional<Recursive> recursive()
  {
    if(canPlayRecursive(one) and canPlayRecursive(two))
      return Recursive({next(one.begin()), next(one.begin(), 1+*one.begin())},
                       {next(two.begin()), next(two.begin(), 1+*two.begin())});
    else
      return {};
  }
  
  bool operator==(auto const &other) const
  {
    return (one==other.one) and (two==other.two);
  }
};

ostream& operator<<(ostream& out, Recursive const & r)
{
  out<< (Game) r;
  return out;
}
