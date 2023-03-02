#include <gtest/gtest.h>
#include <gmock/gmock.h>


using namespace testing;
using namespace std;

#include "counter.hh"
#include "monkey.hh"
#include "types.hh"

auto solutionA(std::vector<Monkey> &vm)
{
  Counter c;
  for(auto i=0;i<20;i++)
    round(vm, c);
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



