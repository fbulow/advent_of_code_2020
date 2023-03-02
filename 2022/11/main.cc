#include <gtest/gtest.h>
#include <gmock/gmock.h>


using namespace testing;
using namespace std;

#include "counter.hh"
#include "monkey.hh"
#include "types.hh"
#include <numeric>

TEST(monkey_oper, no_overflow)
{
  auto sut = Monkey::example()[2];
  EXPECT_THAT(sut.oper(58558), Eq(3429039364));
}

TEST(Example, one_round)
{
  auto vm = Monkey::example();
  Counter c;
  auto pod = productOfDivisors(vm);
  round(vm, c,
	[pod]
	(WorryValue v)
	{
	  return v%pod;
	});
  
  EXPECT_THAT(c[0], Eq(2));
  EXPECT_THAT(c[1], Eq(4));
  EXPECT_THAT(c[2], Eq(3));
  EXPECT_THAT(c[3], Eq(6));

  for(int i =1; i<20;i++)
    round(vm, c,
	  [pod]
	  (WorryValue v)
	  {
	    if(v<=0)
	      assert(v>=0);
	    return v%pod;
	  });
    
EXPECT_THAT(c[0], Eq(99 ));
EXPECT_THAT(c[1], Eq(97 ));
EXPECT_THAT(c[2], Eq(8 ));
EXPECT_THAT(c[3], Eq(103 ));
}

auto solutionB(std::vector<Monkey> &vm)
{
  Counter c;
  auto pod = productOfDivisors(vm);
  for(int i=0;i<10000;i++)
    round(vm, c,
	  [pod]
	  (WorryValue v)
	  {
	    return v%pod;
	  });
  return c.monkeyBusines();
}

TEST(solutionB, input)
{
  auto e = Monkey::input();
  EXPECT_THAT(solutionB(e), Eq(2713310158));
}

TEST(solutionB, example)
{
  auto e = Monkey::example();
  EXPECT_THAT(solutionB(e), Eq(2713310158));
}

TEST(productOfDivisors, example)
{
  EXPECT_THAT(productOfDivisors(Monkey::example()), Eq(23*19*13*17));
}


auto solutionA(std::vector<Monkey> &vm)
{
  Counter c;
  int productOfDivisors = std::accumulate(vm.cbegin(),
					  vm.cend(),
					  1,
					  [](int s, Monkey const &m)
					  {
					    return s*m.getDivisor();
					  });
  for(auto i=0;i<20;i++)
    round(vm, c,
	  [productOfDivisors]
	  (WorryValue v)
	  {
	    return (v/3)%productOfDivisors;
	  });
  return c.monkeyBusines();
}

TEST(solutionA, input)
{
  auto e = Monkey::input();
  EXPECT_THAT(solutionA(e), Eq(119715));
}

TEST(solutionA, example)
{
  auto e = Monkey::example();
  EXPECT_THAT(solutionA(e), Eq(10605));
}

TEST(Monkey, example)
{
  auto data = Monkey::example();
  auto sut =  data[0].pop();
  EXPECT_THAT(sut.destination, Eq(3));
  EXPECT_THAT(sut.value, Eq(500));
}

TEST(monkeyBusiness, example)
{
  Counter sut;
  
  for(int i =0 ;i<101;i++)
    sut.tick(0);
  for(int i =0 ;i<95;i++)
    sut.tick(1);
  for(int i =0 ;i<7;i++)
    sut.tick(2);
  for(int i =0 ;i<105;i++)
    sut.tick(3);

  EXPECT_THAT(sut.monkeyBusines(), Eq(10605));
}



