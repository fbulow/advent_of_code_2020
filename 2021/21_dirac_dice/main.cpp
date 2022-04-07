#include <gtest/gtest.h>
#include "dice.hh"
#include "player.hh"
#include <algorithm>

using namespace std;

Player operator+(Player p, unsigned int steps)
{
  p.move(steps);
  return p;
}

TEST(Player, operatorPlus)
{
  auto sut = Player(1) + 2;
  EXPECT_EQ(3, sut.pos());
}

struct Result{
  long long int aWin;
  long long int bWin;
  long long int worlds() const { return aWin+bWin; }
};

Result operator+(Result const & a,
                 Result const & b)
{
  if(a.aWin > 1000)
    return {
      a.aWin+b.aWin,
      a.bWin+b.bWin};
    
  // assert(a.bWin < 1000);
  // assert(b.aWin < 1000);
  // assert(b.bWin < 1000);
  
  return {
    a.aWin+b.aWin,
    a.bWin+b.bWin};
    
}

TEST(Result, operatorPlus)
{
  auto sut = Result(1,2) + Result(4,8);
  
  EXPECT_EQ(5,  sut.aWin);
  EXPECT_EQ(10, sut.bWin);
}



struct Arg{
  Player a;
  Player b;
  };

bool operator<(Arg const &a, Arg const &b)
{
  if(a.a < b.a)
    return true;
  if(b.a < a.a)
    return false;
  if(a.b < b.b)
    return true;
  else
    return false;
}
TEST(Arg, operatorLess)
{
  EXPECT_TRUE (Arg(1, 1) < Arg(2, 1));
  EXPECT_FALSE(Arg(2, 1) < Arg(1, 1));
  EXPECT_TRUE (Arg(1, 1) < Arg(1, 2));
  EXPECT_FALSE(Arg(1, 1) < Arg(1, 1));
  EXPECT_FALSE(Arg(2, 1) < Arg(1, 2));
}

//Result solutionB(Player a, Player b, int sum=0, int steps = 0);

template<int WIN_SCORE, int CACHE_NUMBER>
Result cache(Player a, Player b, int steps)
{
  if constexpr (CACHE_NUMBER<1)
                 {
                   return solutionB<WIN_SCORE>(a,b, 0, steps);
                 }
  else
    {
      static map<Arg, Result> cache;
      Arg arg(a,b);
      auto it = cache.find(arg);
      if(it!=cache.end())
        return it->second;
      else
        {
          Result ret  = solutionB<WIN_SCORE>(a,b, 0, steps);
          cache[arg] = ret;
          return ret;
        }
    }
}


template<int WIN_SCORE, int CACHE_COUNT=2>
Result solutionB(Player a, Player b, int sum=0, int steps=0)
{
  auto isWinner = [](auto const &p){return p.score()>=WIN_SCORE;};
  
  switch(steps%8)
    {
    case 0:
    case 1:
    case 2:

    case 4:
    case 5:
    case 6:

      return
        solutionB<WIN_SCORE>(a, b, sum+1, steps+1)+
        solutionB<WIN_SCORE>(a, b, sum+2, steps+1)+
        solutionB<WIN_SCORE>(a, b, sum+3, steps+1);

    case 3:
      a.move(sum);
      if(isWinner(a))
        return Result(1,0);
      else
        {
          return
            //solutionB(a, b, 0, steps+1)
            cache<WIN_SCORE, 10*CACHE_COUNT>(a, b, steps+1)
            ;
        }

    case 7:
      b.move(sum);
      if(isWinner(b))
        return Result(0,1);
      else
        return
          //solutionB(a, b, 0, steps+1)
          cache<WIN_SCORE, CACHE_COUNT-1>(a, b, steps+1)
          ;
    }
  assert(false);
  // return
  //   {444356092776315,
  //    341960390180808};
}



TEST(number_of_worlds, a_wins)
{
  auto sut = solutionB<21>({1,20},4);
  ASSERT_EQ(27, sut.worlds());
  ASSERT_EQ(27, sut.aWin);
}

TEST(number_of_worlds, b_wins)
{
  auto sut = solutionB<21>(1,{4,20});
  EXPECT_EQ(27*27, sut.worlds());
  EXPECT_EQ(27*27, sut.bWin);
}

TEST(number_of_worlds, a_wins_once_then_b_wins)
{
  auto sut = solutionB<21>({1,11},{4,20});
  EXPECT_EQ(1, sut.aWin);
  EXPECT_EQ(26*27, sut.bWin);
}


TEST(solution, is_cache_broken)
{
  auto a = solutionB<15,2>(1,1).worlds();
  auto b = solutionB<15,1>(1,1).worlds();
  auto c = solutionB<15,0>(1,1).worlds();
  
  
  EXPECT_EQ(a,b);
  EXPECT_EQ(b,c);
             
}

TEST(solution, b)
{
  
  auto sut = solutionB<21>(1,4);
  EXPECT_EQ(444356092776315+341960390180808,
            sut.worlds());
  // EXPECT_EQ(444356092776315,
  //           sut.aWin);
  // EXPECT_EQ(341960390180808,
  //           sut.bWin);
    
}


