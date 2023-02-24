#include <gtest/gtest.h>
#include <gmock/gmock.h>


using namespace testing;
using namespace std;

#include "counter.hh"

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



