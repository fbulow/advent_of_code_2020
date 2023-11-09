#include <functional>
#include <set>
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

class Topology
{
public:
  Topology(Input const & inp){}

  Flow flowRate(Valve const &v) const
  {
    if(v == "AA")
      return 0;
    if(v == "BB")
      return 13;
    if(v == "CC")
      return 2;
    if(v == "DD")
      return 20;
    if(v == "EE")
      return 3;
    if(v == "FF")
      return 0;
    if(v == "GG")
      return 0;
    if(v == "HH")
      return 22;
    if(v == "II")
      return 0;
    if(v == "JJ")
      return 21;

    return 0;
  }
  
  Minutes costToOpen(Valve const & p, Valve const & t) const
  {
    if((p == "AA") && (t == "DD"))return 2  - 0		;
    if((p == "DD") && (t == "BB"))return 5  - 2		; 
    if((p == "BB") && (t == "JJ"))return 9  - 5		;
    if((p == "JJ") && (t == "HH"))return 17 - 9		;
    if((p == "HH") && (t == "EE"))return 21 - 17	;
    if((p == "EE") && (t == "CC"))return 24 - 21	;

    return 1000;
  }
};

class TotalFlow
{
  Flow value_;
public:
  TotalFlow(Flow v=0)
    :value_(v)
  {}
  TotalFlow(Input const &)
  {}

  TotalFlow open(Minutes remainingTime, Flow flow) const
  {
    return TotalFlow(value_ + remainingTime*flow);

  }
  Flow value() const
  {
    return value_;
  }
  
};

struct State
{
  static State initial()
  {
    return {"AA", 30, 0,
	    {
	      "DD",
	      "BB",
	      "JJ",
	      "HH",
	      "EE",
	      "CC"}};
  }
  
  Valve position = "";
  Minutes timeLeft = 30;
  TotalFlow flow = 0;
  std::set<Valve> notVisited = {};

  State goTo(Valve dest, Minutes remainingTime, Flow flowRate) const
  {
    return {
      .position = dest,
      .timeLeft = remainingTime,
      .flow = flow.open(remainingTime, flowRate),
      .notVisited = [this, dest](){
	std::set<Valve> ret;
	std::copy_if(notVisited.begin(), notVisited.end(),
		     std::inserter(ret, ret.end()),
		     [dest](auto const &x)
		     {return x!=dest;}
		     );
	return ret;
      }()
    };
  }
  
};


void forEachPath(std::function<void(Flow)> &callback, Topology const & t, State const &s)
{
  if(s.timeLeft < 1) return;
  
  callback(s.flow.value());
  for(auto const &x: s.notVisited)
    forEachPath(callback, t, s.goTo(x
				    ,s.timeLeft-t.costToOpen(s.position, x)
				    ,t.flowRate(x)));
}


Flow SolA(Input const &inp)
{
  MaxValueGetter ret;
  auto callback = std::function<void(Flow)>([&ret](auto x)
  {
    ret(x);
  });
  
  forEachPath(callback, Topology(inp), State::initial());

  return ret.value();
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(State, goTo)
{
  auto const sut = State::initial().goTo("JJ", 28, 20);
  EXPECT_THAT(sut.position, Eq("JJ"));
  EXPECT_THAT(sut.timeLeft, Eq(28));
  EXPECT_THAT(sut.flow.value(), Eq(28*20));

  EXPECT_FALSE(sut.notVisited.contains("JJ"));
  EXPECT_TRUE(sut.notVisited.contains("DD"));
}

TEST(forEachPath, do_nothing_if_remaining_time_is_less_than_one)
{
  bool called{false};

  std::function<void(Flow)> callback = [&called](Flow f){called=true;};
  forEachPath(callback,
	      Topology(Input()),
	      State("",
		    0,
		    22,
		    std::set<Valve>{})
	      );

  EXPECT_FALSE(called);
}


TEST(forEachPath, return_if_you_cant_do_anything)
{
  Flow ret{0};
  int callCount{0};
  std::function<void(Flow)> callback = [&ret, &callCount](Flow f){ret=f;callCount++;};
  forEachPath(callback,
	      Topology(Input()),
	      State("",
		    1,
		    22,
		    std::set<Valve>{})
	      );

  EXPECT_THAT(ret, Eq(22));
  EXPECT_THAT(callCount, Eq(1));
    
}
 
TEST(TotalFlow, best_exmaple_sequence)
{
  EXPECT_THAT(TotalFlow(example())
	      .open(30-2 , 20)	//DD
	      .open(30-5 , 13)	//BB
	      .open(30-9 , 21)	//JJ
	      .open(30-17, 22)	//HH
	      .open(30-21, 3 )	//EE
	      .open(30-24, 2 )	//CC
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
