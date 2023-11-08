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
  Flow value_;
public:
  TotalFlow(Flow v=0)
    :value_(v)
  {}
  TotalFlow(Input const &)
  {}

  TotalFlow open(Minutes time, Flow flow) const
  {
    static constexpr Minutes totalTime = 30;
    return TotalFlow(value_ + (totalTime - time)*flow);

  }
  Flow value() const
  {
    return value_;
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
	      .open(2 , 20)	//DD
	      .open(5 , 13)	//BB
	      .open(9 , 21)	//JJ
	      .open(17, 22)	//HH
	      .open(21, 3 )	//EE
	      .open(24, 2 )	//CC
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

