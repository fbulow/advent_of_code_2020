#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <functional>

using namespace testing;


bool shouldBeLogged(int cycle)
{
  if(cycle<60)
    return cycle==20;
  else
    return not((cycle-20)%40);
}

using Log = std::function<void(int, int)>; //Cycle, value
Log noLog = [](int,int){};

struct Signal{
  int cycle=1;
  int value=1;

  Signal noop(Log& log = noLog) const
  {
    log(cycle, value);
    return {
      cycle+1,
      value
    };
  }
  Signal addx(int x, Log& log = noLog) const
  {
    log(cycle,  value);
    log(cycle+1, value);
    return {cycle+2,
	    value+x};
  }
};


TEST(shouldBeLogged, all)
{
  ASSERT_FALSE(shouldBeLogged(0));
  ASSERT_TRUE(shouldBeLogged(20));
  ASSERT_FALSE(shouldBeLogged(40));
  ASSERT_TRUE(shouldBeLogged(60));
  ASSERT_FALSE(shouldBeLogged(80));
  ASSERT_TRUE(shouldBeLogged(100));
  ASSERT_FALSE(shouldBeLogged(119));
}

TEST(noop, test)
{
  auto sut = Signal().noop();
  EXPECT_THAT(sut.cycle, Eq(2));
  EXPECT_THAT(sut.value, Eq(1));
}

TEST(addx, test)
{
  auto sut = Signal().addx(5);
  EXPECT_THAT(sut.cycle, Eq(3));
  EXPECT_THAT(sut.value, Eq(6));
}

#include <fstream>

void runCommandLoop(std::istream &in, Log &log)
{
  Signal sut;
  std::string command;
  int value;
  
  in>> command;
  while(not in.eof())
    {
      if( command == "noop" )
	sut = sut.noop(log);
      else
	{
	  in>> value;
	  sut = sut.addx(value, log);
	}
      in>> command;
    }
}

auto solutionA(std::istream &in)
{
  long long int signalStrength{0};
  Log log = [&signalStrength](int cycle, int value)
  {
    if(shouldBeLogged(cycle))
      signalStrength+=cycle*value;
  };
  runCommandLoop(in, log);
  return signalStrength;
}

TEST(SolutionA, example)
{
  std::ifstream in(EXAMPLE);

  EXPECT_THAT(solutionA(in), Eq(13140));
}

TEST(SolutionA, input)
{
  std::ifstream in(INPUT);

  EXPECT_THAT(solutionA(in), Eq(11820));
}

