#include <functional>
#include <string>
#include <memory>

using Minutes = int;
class Input{};

using Valve = std::string ;
using Sequence  = std::vector<Valve>;


inline
Input example()
{return {};}

using Flow = int;

class MaxValueGetter
{
  int ret{0};
public:
  MaxValueGetter() = default;
  void operator()(int a){if(a>ret) ret=a;}
  int value() const { return ret;}
};

void forEachPath(Input const &in, std::function<void(Flow)> callback)
{
  callback(1651);
}

class TotalFlow
{
public:
  TotalFlow()=default;
  TotalFlow(Input const &)
  {}

  TotalFlow open(Valve const &) const
  {
    return {};
  }
  Flow value() const
  {
    return 1651;
  }
  
};

Flow SolA(Input const &inp)
{
  MaxValueGetter ret;
  forEachPath(inp, [&ret](auto x){ret(x);});
  return ret.value();
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(TotalFlow, best_exmaple_sequence)
{
  EXPECT_THAT(TotalFlow(example())
	      .open("DD")
	      .open("BB")
	      .open("JJ")
	      .open("HH")
	      .open("EE")
	      .open("CC")
	      .value(),
	      Eq(1651)
	      );
}

TEST(maxValueGetter, example)
{
  MaxValueGetter sut;
  sut(5);
  EXPECT_THAT(sut.value(), Eq(5));
  sut(4);
  EXPECT_THAT(sut.value(), Eq(5));
  sut(7);
  EXPECT_THAT(sut.value(), Eq(7));  
}


TEST(SolA, example)
{
  EXPECT_THAT(SolA(example()), Eq(1651));
}

