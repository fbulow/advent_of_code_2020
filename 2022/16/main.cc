#include <functional>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include <optional>
#include <cassert>

using Minutes = int;
using Valve = std::string ;
using Flow = int;

template<class T>
T example()
{
  auto in = std::ifstream(EXAMPLE);
  return {in};
}

std::string stripComma(std::string const &s)
{
  if(','!=*s.rbegin())
    return s;
  else
    return {s.begin(), std::next(s.end(), -1)};
}

class RelevantGetter
{
  using Cb = std::function<void(Valve const & v, Flow const &f, std::set<Valve> &&)>;
  
  Cb cb;
  Valve v;
  std::optional<Flow> flow;
  std::set<Valve>  adjacent;
public:
  RelevantGetter(Cb &&f)
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
  
  RelevantGetter& operator<<(std::string const & word)
  {
    static const std::set<std::string> ignore{"has", "flow", "tunnels", "tunnel", "lead", "to", "valves"};
    
    if(ignore.contains(word))
       return *this;
    else if((word=="Valve") or word.empty())
      {
	if(!v.empty())
	  {
	    cb(v, flow.value(), std::move(adjacent));
	    v.clear();
	    flow.reset();
	    adjacent = {};
	  }
      }
    else if(v.empty())
      v = word;
    else if(!flow)
      flow = getRate(word);
    else
      adjacent.insert(stripComma(word));
    return *this;
  }
  
};

class Input
{
  std::set<Valve> allNodes_;
  std::set<Valve> notVisited_;
  std::map<Valve,Flow> flowRate_{};
  std::map<Valve,std::set<Valve>> adjacent_;
public:
  [[nodiscard]]
  std::set<Valve> const & allNodes() const
  {
    return allNodes_;
  }

  [[nodiscard]]
  Flow flowRate(Valve const &v) const 
  {
    auto it = flowRate_.find(v);
    assert(it != flowRate_.end());
    return it->second;
  }

  [[nodiscard]]
  std::set<Valve> adjacent(Valve const &v) const
  {
    auto it = adjacent_.find(v);
    assert(it!=adjacent_.end());
    return it->second;
  }
  
  Input(std::istream &in)
  {
    RelevantGetter rg(
		      [this](Valve const &v, Flow f, std::set<Valve> &&a)
		      {
			allNodes_.insert(v);
			adjacent_[v]=std::move(a);
			flowRate_[v]=f;
			if(f>0)
			  notVisited_.insert(v);
		      });
    std::string s;
    in>>s;
    while(!s.empty())
      {
	rg<<s;
	s.clear();
	in>>s;
      }
    rg<<""; // flush
  }

  std::set<Valve> notVisited() const
  {
    return notVisited_;
  }
};

using Sequence  = std::vector<Valve>;


inline
Input example()
{
  std::ifstream in(EXAMPLE);
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

class Topology : public Input
{

public:
  Topology() = default;
  Topology(std::istream &in)
    :Input(in)
  {
  }
  
  Minutes costToOpen(Valve const & p, Valve const & t) const
  {
    if(p==t) return 1;

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


Flow SolA(Topology const &t)
{
  MaxValueGetter ret;
  auto callback = std::function<void(Flow)>([&ret](auto x)
  {
    ret(x);
  });
  auto s = State::initial(t.notVisited());
  forEachPath(callback, t, s);

  return ret.value();
}



#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

using ValveSet = std::set<Valve>;

enum class Region { Outside, Edge, Inside };

class Regions{
  std::map<Valve, Region> data;
public:
  Regions(ValveSet const &outer)
  {
    for(Valve const &v: outer)
      data[v]=Region::Outside;
  }
  static Region step(Region before)
  {
    switch(before)
      {
      case Region::Outside:
	return Region::Outside;
      case Region::Edge:
	return Region::Inside;
      case Region::Inside:
	return Region::Inside;
      }
    assert(false);
  }
  void moveEdge(ValveSet const&v)
  {
    for(auto &x: data)
      {
	if(v.contains(x.first))
	  x.second = Region::Edge;
	else
	  x.second = step( x.second );
      }
  }

  [[nodiscard]]
  ValveSet region(Region r) const
  {
    ValveSet ret;
    for(auto const &x: data)
      if(x.second==r)
	ret.insert(x.first);
    return ret;
  }
};

using ForEachDistanceCallback = std::function<void(Valve const & start, Valve const & end, Minutes costToOpen)>;

void forEachDistance(ForEachDistanceCallback& ret,
		     Input const &i, Valve start, Minutes time)
{
  Regions r(i.allNodes());
  r.moveEdge({start});

  Minutes cost=1;
  while((++cost)<time)
    {
      ValveSet newEdge;
      for(Valve const &e: r.region(Region::Edge))
	{
	  for(Valve const & x: i.adjacent(e))
	    if(!r.region(Region::Inside).contains(x))
	      newEdge.insert(x);
	}
      for(auto const& x: newEdge)
	ret(start, x, cost);
      r.moveEdge(newEdge);
    }
  
}

TEST(forEachDistance, call_with_a_j)
{
  Minutes cost{-1};

  ForEachDistanceCallback callback = [&cost](auto a, auto b, auto c){if((a=="AA") and (b=="JJ")) cost=c;};
  
  forEachDistance(callback,
		  example<Input>(),
		  "AA",
		  5);
  EXPECT_THAT(cost, Eq(3));
}


TEST(forEachDistance, call_with_a_d)
{
  Minutes costAaDd{-1};

  ForEachDistanceCallback callback =
    [&costAaDd]
    (auto a, auto b, auto cost)
    {
      if((a=="AA") and (b=="DD"))
	costAaDd=cost;
    };
  
  forEachDistance(callback,
		  example<Input>(),
		  "AA",
		  5);
  EXPECT_THAT(costAaDd, Eq(2));
}


TEST(Regions_, moveEdge_)
{
  auto sut = Regions({"A", "B", "C"});
  sut.moveEdge({"A"});
  EXPECT_THAT(sut.region(Region::Inside), Eq(ValveSet{}));
  EXPECT_THAT(sut.region(Region::Outside), Eq(ValveSet{"B", "C"}));
  EXPECT_THAT(sut.region(Region::Edge), Eq(ValveSet{"A"}));

  sut.moveEdge({"B"});
  EXPECT_THAT(sut.region(Region::Inside), Eq(ValveSet{"A"}));
  EXPECT_THAT(sut.region(Region::Outside), Eq(ValveSet{"C"}));
  EXPECT_THAT(sut.region(Region::Edge), Eq(ValveSet{"B"}));
}

TEST(Topology, costToOpen)
{
  auto sut = example<Topology>();
  
    EXPECT_THAT(sut.costToOpen("AA", "DD"), Eq(2  - 0	));
    EXPECT_THAT(sut.costToOpen("DD", "BB"), Eq(5  - 2	)); 
    EXPECT_THAT(sut.costToOpen("BB", "JJ"), Eq(9  - 5	));
    EXPECT_THAT(sut.costToOpen("JJ", "HH"), Eq(17 - 9	));
    EXPECT_THAT(sut.costToOpen("HH", "EE"), Eq(21 - 17	));
    EXPECT_THAT(sut.costToOpen("EE", "CC"), Eq(24 - 21	));

}

TEST(Input, allNodes)
{
  EXPECT_THAT(example<Input>().allNodes().size(), Eq(10));
}

TEST(Input, adjacent)
{
  EXPECT_THAT(example<Input>().adjacent("AA"), Eq(std::set<Valve>{"DD", "II", "BB"}));
}

TEST(Input, flowRate_example)
{
  auto sut = example<Input>();

  EXPECT_THAT(sut.flowRate("AA"), Eq( 0 ));
  EXPECT_THAT(sut.flowRate("BB"), Eq( 13 ));
  EXPECT_THAT(sut.flowRate("CC"), Eq( 2 ));
  EXPECT_THAT(sut.flowRate("DD"), Eq( 20 ));
  EXPECT_THAT(sut.flowRate("EE"), Eq( 3 ));
  EXPECT_THAT(sut.flowRate("FF"), Eq( 0 ));
  EXPECT_THAT(sut.flowRate("GG"), Eq( 0 ));
  EXPECT_THAT(sut.flowRate("HH"), Eq( 22 ));
  EXPECT_THAT(sut.flowRate("II"), Eq( 0 ));
  EXPECT_THAT(sut.flowRate("JJ"), Eq( 21 ));
}

TEST(RelevantValveGetter, getRate)
{
  EXPECT_THAT(RelevantGetter::getRate("rate=13;"),
	      Eq(13));
}

TEST(RelevantValveGetter, dont_flush_if_blow_is_empty)
{
  int callCount{0};
  auto sut = RelevantGetter([&callCount](Valve const&, Flow const&, auto){callCount++;});
  sut<<"";
  EXPECT_THAT(callCount, Eq(0));  
}

TEST(RelevantValveGetter, add_multiple_rows )
{
  int callCount{0};
  Valve v;
  Flow f;
  auto sut = RelevantGetter(
			    [&callCount, &v, &f](Valve const& v_, Flow const& f_, auto)
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
  auto sut = RelevantGetter(
			    [&callCount, &v, &f](Valve const& v_, Flow const& f_, auto)
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
	      example<Topology>(),
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
	      example<Topology>(),
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
  EXPECT_THAT(SolA(example<Topology>()), Eq(1651));
}
