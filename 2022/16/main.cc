#include <functional>
#include <set>
#include <string>
#include <memory>
#include <sstream>
#include <optional>
#include <cassert>

using Minutes = int;
using Valve = std::string ;
using Flow = int;


class RelevantValveGetter
{
  using Cb = std::function<void(Valve const & v, Flow const &f)>;
  
  Cb cb;
  enum class State { Dark, GotValve, };
  State s = State::Dark;
  Valve v;
  std::optional<Flow> flow;
public:
  RelevantValveGetter(Cb &&f)
    :cb(std::move(f))
  {}

  static Flow getRate(std::string const &s)
  {
    std::istringstream in({next(s.begin(),5), s.end()});
    Flow ret{-1};
    in>>ret;
    assert(ret!=-1);
    return ret;
  }
  
  RelevantValveGetter& operator<<(std::string const & word)
  {
    static const std::set<std::string> ignore{"has", "flow", "tunnels", "tunnel", "lead", "to", "valves"};
    
    if(ignore.contains(word))
       return *this;
    else if((word=="Valve") or word.empty())
      {
	if(!v.empty())
	  {
	    cb(v, flow.value());
	    v.clear();
	    flow.reset();
	  }
      }
    else if(v.empty())
      v = word;
    else if(!flow)
      flow = getRate(word);
    else
      {}
    return *this;
  }
  
};

class Input
{
  std::set<Valve> notVisited_;
public:
  Input(std::istream &in)
  {
    std::string ret;
    in>>ret;
    // while(!ret.empty())
    //   {
	
    //   }
  }

  static
  Input example()
  {
    auto in = std::istringstream(EXAMPLE);
    return {in};
  }

  std::set<Valve> notVisited() const
  {
    return {"DD", "BB", "JJ", "HH", "EE", "CC"};
  }
};

using Sequence  = std::vector<Valve>;


inline
Input example()
{
  std::istringstream in(EXAMPLE);
  return {in};
}

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
    :TotalFlow()
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
  static State initial(std::set<Valve> notVisited)
  {
    return {"AA", 30, 0,
	    std::move(notVisited)};
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
  auto s = State::initial(inp.notVisited());
  forEachPath(callback, Topology(inp), s);

  return ret.value();
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(RelevantValveGetter, getRate)
{
  EXPECT_THAT(RelevantValveGetter::getRate("rate=13;"),
	      Eq(13));
}

TEST(RelevantValveGetter, dont_flush_if_blow_is_empty)
{
  int callCount{0};
  auto sut = RelevantValveGetter([&callCount](Valve const&, Flow const&){callCount++;});
  sut<<"";
  EXPECT_THAT(callCount, Eq(0));  
}

TEST(RelevantValveGetter, add_multiple_rows )
{
  int callCount{0};
  Valve v;
  Flow f;
  auto sut = RelevantValveGetter(
				 [&callCount, &v, &f](Valve const& v_, Flow const& f_)
				 {
				   callCount++;
				   v = v_;
				   f = f_;
				 });
  sut<<"Valve"<< "BB"<< "has"<< "flow"<< "rate=13;"<< "tunnels"<< "lead"<< "to"<< "valves"<< "CC";
  EXPECT_THAT(callCount, Eq(0));
  sut<<"Valve";
  EXPECT_THAT(callCount, Eq(1));
  EXPECT_THAT(f, Eq(13));
  sut << "BB"<< "has"<< "flow"<< "rate=14;"<< "tunnels"<< "lead"<< "to"<< "valves"<< "CC"
     <<"";
  EXPECT_THAT(callCount, Eq(2));
  EXPECT_THAT(f, Eq(14));
}

TEST(RelevantValveGetter, add_single_row )
{
  int callCount{0};
  Valve v;
  Flow f;
  auto sut = RelevantValveGetter(
				 [&callCount, &v, &f](Valve const& v_, Flow const& f_)
				 {
				   callCount++;
				   v = v_;
				   f = f_;
				 });
  
  sut<<"Valve";
  sut<< "BB"<< "has"<< "flow"<< "rate=13;"<< "tunnels"<< "lead"<< "to"<< "valves"<< "CC";
  sut<<"";
  ASSERT_THAT(callCount, Eq(1));
  EXPECT_THAT(v, Eq("BB"));
  EXPECT_THAT(f, Eq(13));
}


TEST(Input, example)
{
  auto ref = std::set<Valve>
    {
      "BB",
      "CC",
      "DD",
      "EE",
      "HH",
      "JJ"
    };
  
  EXPECT_THAT(example().notVisited(), Eq(ref));

}

TEST(State, goTo)
{
  auto const sut = State::initial({"JJ","DD"}).goTo("JJ", 28, 20);
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
	      Topology(Input::example()),
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
	      Topology(Input::example()),
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
