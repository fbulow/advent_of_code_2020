#include <functional>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include <optional>
#include <cassert>
#include <algorithm>

using Minutes = int;
using Valve = std::string ;
using Flow = int;
using ForEachDistanceCallback = std::function<void(Valve const & start, Valve const & end, Minutes costToOpen)>;


//TODO modules

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
  std::set<Valve> const & notVisited() const{return notVisited_;}

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

void forEachDistance(ForEachDistanceCallback& ret,
		     Input const &i, Valve start, Minutes time);



class Topology : public Input
{
  struct TargetAndCost
  {
    Valve target;
    Minutes cost;
  };
  std::map<Valve, std::vector<TargetAndCost>> data_;
  
  
public:
  Topology() = default;
  Topology(std::istream &in, Valve const & startAt="AA", Minutes totalTime=30)
    :Input(in)
  {
    struct SecondaryStartingPoint{
      Valve start;
      Minutes timeLeft;
    };
    std::vector<SecondaryStartingPoint> secondaryStarts;
    
    ForEachDistanceCallback populate =
      [this](Valve const & start, Valve const & end, Minutes costToOpen)
      {
	data_[start].emplace_back(end, costToOpen);
      };

    ForEachDistanceCallback popAndAdd =
      [&populate, &secondaryStarts, totalTime]
      (Valve const & start, Valve const & end, Minutes costToOpen)
      {
	populate(start, end, costToOpen);
	secondaryStarts.emplace_back(end, totalTime-costToOpen);
      };

    
    forEachDistance(popAndAdd,
		    *this, startAt, totalTime);

    for(auto const &ss : secondaryStarts)
      {
	forEachDistance(populate,
			*this, ss.start, ss.timeLeft);
	
      }
      
  }
  
  Minutes costToOpen(Valve const & p, Valve const & t) const
  {
    static constexpr Minutes never = 100000;
    
    auto it = data_.find(p);
    if(it==data_.end()) return never;

    auto const &v = it->second;
    
    auto iit = std::find_if(v.begin(), v.end(), [t](auto const &x){return x.target==t;});
    if(iit == v.end()) return never;
    else return iit->cost;
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

class StateA 
{
  
  Valve position_ = "";
  Minutes timeLeft_ = 30;
  TotalFlow flow_ = 0;
  std::set<Valve> notVisited_ = {};
public:
  StateA(Valve position_, Minutes timeLeft, TotalFlow flow_, std::set<Valve> notVisited_={})
    :position_(position_)
    ,timeLeft_(timeLeft)
    ,flow_(flow_)
    ,notVisited_(std::move(notVisited_))
  {}

  [[nodiscard]]
  Valve const & position() const {return position_;}
  
  [[nodiscard]]
  std::set<Valve> const & notVisited() const {return notVisited_;}
  
  static StateA initial(std::set<Valve> notVisited)
  {
    return StateA(Valve("AA"), 30, 0,
		  std::move(notVisited));
  }
  Minutes timeLeft() const{return timeLeft_;}
  TotalFlow flow() const{return flow_;}
  StateA goTo(Valve dest, Minutes remainingTime, Flow flowRate) const
  {
    return StateA(dest,
		  remainingTime,
		  flow_.open(remainingTime, flowRate),
		  [this, dest](){
		    std::set<Valve> ret;
		    std::copy_if(notVisited_.begin(), notVisited_.end(),
				 std::inserter(ret, ret.end()),
				 [dest](auto const &x)
				 {return x!=dest;}
				 );
		    return ret;
		  }()
		  );
  }
};

using Player = std::tuple<Minutes, Valve>;

class Positions : std::set<Player>
{
 public:
  Positions() = default;
  Positions(std::set<Player> inp) :std::set<Player>(std::move(inp))
  {}
  static Positions initial(){return Positions({{26, "AA"}});};

  [[nodiscard]]
  Valve position() const {return std::get<Valve>(*rbegin());}

  [[nodiscard]]
  Player currentPlayer() const {return *rbegin();} 
  
  [[nodiscard]]
  Positions goTo(Valve dest, Minutes remainingTime) const
  {
    Positions ret;
    ret.insert(*begin());
    ret.insert({remainingTime, dest});
    return ret;
  }
};

class StateB
{
  Positions p;
  TotalFlow flow_ = 0;
  std::set<Valve> notVisited_ = {};
  public:
  StateB(Positions position, TotalFlow flow, std::set<Valve> notVisited={})
    :p(std::move(position))
    ,flow_(std::move(flow))
    ,notVisited_(std::move(notVisited))

  {}

  [[nodiscard]]
  auto const & notVisited() const {return notVisited_;}

  
  [[nodiscard]]
  TotalFlow const& flow() const {return flow_;}
  
  [[nodiscard]]
  Valve position() const {return std::get<Valve>(p.currentPlayer());}

  StateB goTo(Valve dest, Minutes remainingTime, Flow flowRate) const
  {
    return StateB(p.goTo(dest, remainingTime),
		  flow_.open(remainingTime, flowRate),
		  [this, dest](){
		    std::set<Valve> ret;
		    std::copy_if(notVisited_.begin(), notVisited_.end(),
				 std::inserter(ret, ret.end()),
				 [dest](auto const &x)
				 {return x!=dest;}
				 );
		    return ret;
		  }());
    
  }
  
  static StateB initial(std::set<Valve> notVisited) 
  {
    std::set<Player> s;
    s.insert(Player{26, Valve("AA")});
    return StateB(s,
		  0,
		  notVisited);
  }

  [[nodiscard]]
  Minutes timeLeft() const
  {
    return std::get<Minutes>(p.currentPlayer());
  }
};



template<class STATE>
void forEachPath(std::function<void(Flow)> &callback, Topology const & t, STATE const &s)
{
  if(s.timeLeft() < 1) return;
  
  callback(s.flow().value());
  for(auto const &x: s.notVisited())
    forEachPath(callback, t, s.goTo(x
				    ,s.timeLeft()-t.costToOpen(s.position(), x)
				    ,t.flowRate(x)));
}



Flow SolB(Topology const &t)
{
  MaxValueGetter ret;
  auto callback = std::function<void(Flow)>([&ret](auto x)
  {
    ret(x);
  });
  forEachPath(callback, t, StateB::initial(t.notVisited()));
  return ret.value();
}


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


class Checklist
{

  Topology t_;
  Valve pos_{"AA"};
  Minutes timeLeft_;
  std::set<Valve> notVisited_;
 public:
  Minutes timeLeft() const {return timeLeft_;}
  Topology const & t() const {return t_;}
  Checklist(Topology const &_t, Minutes minutesLeft)
    :timeLeft_(minutesLeft)
    ,notVisited_(_t.notVisited())
    ,t_(_t)
  {}

  Checklist(Checklist const &other)
    :t_(other.t_)
    ,notVisited_(other.notVisited_)
    ,timeLeft_(other.timeLeft_)
  {}

  Checklist& operator=(Checklist &&other)    
  {
    t_=other.t_;
    timeLeft_=other.timeLeft_;
    notVisited_ = std::move(other.notVisited_);
    return *this;
  }
  
  Checklist(Checklist const &other, Valve const &dest)
    :pos_(dest)
    ,timeLeft_(other.timeLeft_-other.costToOpen(dest))
    ,notVisited_([other, dest]//evaluated immediately
		 {
		   decltype(notVisited_) ret;//(other.notVisited_.size()-1);
		   std::ranges::copy_if(other.notVisited_.begin(),
					other.notVisited_.end(),
					std::inserter(ret, ret.end()),
					[dest](Valve const &v)
					{return dest!=v;});
		   return ret;
		 }())
    ,t_(other.t_)
  {}
  
  [[nodiscard]]
  std::vector<Valve> options() const
  {
    std::vector<Valve> ret;
    ret.reserve(t_.notVisited().size());
    auto nv = t_.notVisited();
    copy_if(nv.begin(), nv.end(),
	    std::back_inserter(ret),
	    [this](Valve const& v)
	    {
	      return valueOfOpening(v)>0 ;
	    });
    return ret;
  }

  [[nodiscard]]
  Flow valueOfOpening(Valve const &v) const
  {
    return (timeLeft()- t_.costToOpen(pos_, v)) * t_.flowRate(v);
  }
  
  [[nodiscard]]
  Valve const & pos() const {return pos_;}


  [[nodiscard]]
  Minutes costToOpen(Valve const & v) const 
  {
    return t().costToOpen(pos(), v);
  }
    
  
  [[nodiscard]]
  Checklist tic(Valve const & v) const
  {
    return Checklist(*this, v);
  }
};

auto evaluate(auto const & checklist) //TODO concepts!
{
  auto opt = checklist.options();
  if(opt.empty())
    return 0;
  else
    {
      Flow ret{0};
      for(auto const &o:opt)
	ret = std::max(ret,
		       checklist.valueOfOpening(o)
		       +evaluate(checklist.tic(o)));
      return ret;
    }
}

Flow SolA(Topology const &t)
{
  //New solution
  return evaluate(Checklist(t,30));

  //Old solution
  MaxValueGetter ret;
  auto callback = std::function<void(Flow)>([&ret](auto x)
  {
    ret(x);
  });
  auto s = StateA::initial(t.notVisited());
  forEachPath(callback, t, s);

  return ret.value();
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;


TEST(Checklist_valueOfOpening, example)
{
  auto t = example<Topology>();
  auto sut = Checklist(t, 30);

  EXPECT_THAT(sut.valueOfOpening("DD"), Eq(28*20));
  EXPECT_THAT(sut.costToOpen("DD"), Eq(2));
}

TEST(Checklist_valueOfOpening, example_fail)
{
  auto t = example<Topology>();
  auto sut = Checklist(t, 30);
  EXPECT_THAT(sut.tic("DD").timeLeft(), Eq(28));
}


TEST(Checklist, example)
{
  auto sut = Checklist(example<Topology>(), 30);
  Flow sum = 0;
  Valve v = "AA";


  EXPECT_THAT(sut.timeLeft(), Eq(30));
  v = "DD";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);

  EXPECT_THAT(sut.timeLeft(), Eq(28));
  EXPECT_THAT(sum, Eq(27*20));
  
  v = "BB";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);
  
  v = "JJ";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);

  v = "JJ";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);

  v = "HH";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);

  v = "EE";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);

  v = "CC";
  sum+= sut.valueOfOpening(v);
  sut = sut.tic(v);
  
  EXPECT_THAT(sum, Eq(1651));
  
}

TEST(evaluate, example_but_only_two_steps)
{
  auto t = example<Topology>();
  EXPECT_THAT(Checklist(t, 3).options(), UnorderedElementsAre("BB","DD"));
  
  EXPECT_THAT(evaluate(Checklist(t, 3)), Eq(20)); //Go to DD and open it
}


TEST(Checklist, no_minutes_equals_no_options)
{
  {
    auto t = example<Topology>();
    ASSERT_THAT(t.costToOpen("AA", "BB"), Eq(2));
  }

  {
    auto sut = Checklist(example<Topology>(), 3);
    EXPECT_THAT(sut.tic("BB").options(), UnorderedElementsAre());
  }
}

TEST(evaluate, no_more_options)
{
  struct
  {
    std::vector<Valve> options() const {return {};}
    Minutes valueOfOpening(Valve const &) const
    {
      return 1;//i.e. not 0
    }
    Checklist tic(Valve v) const {assert(false);};
  } sut;
  
  EXPECT_THAT(evaluate(sut), Eq(0));
}

TEST(Checklist, example_check_BB)
{
  auto t = example<Topology>();
  EXPECT_THAT(Checklist(t, 5).tic("BB").options(),
	      UnorderedElementsAre("CC"));
}


TEST(Checklist, example_options)
{
  auto t = example<Topology>();
  auto sut = Checklist(t, 1);

  EXPECT_THAT(sut.options().size(), Eq(0));
}

TEST(Checklist, example_2)
{
  auto t = example<Topology>();

  ASSERT_FALSE(t.notVisited().contains("II"));
}

TEST(StateB, Ordered_inital)
{
  auto sut = Positions::initial();
  
  // auto sut = StateB::initial({"AA","B","C"});
  EXPECT_THAT(sut.position(), Eq("AA"));
}
TEST(StateB, Ordered)
{
  auto sut = Positions::initial();
  EXPECT_THAT(sut
	      .goTo("B", 24)
	      .position(),
	      Eq("AA")); // Player with most time left is still at AA
}

TEST(StateB, Ordered_b)
{
  auto sut = Positions::initial();
  EXPECT_THAT(sut
	      .goTo("B", 24)
	      .goTo("C", 20)
	      .position(),
	      Eq("B")); // Player with most time left is at B
}

TEST(StateB, Ordered_b_reverse_order) //just to be sure
{
  {
    auto sut = Positions::initial();
    EXPECT_THAT(sut
		.goTo("B", 24)
		.goTo("C", 25)
		.position(),
		Eq("C")); // Player with most time left is C
  }
  {
    auto sut = Positions::initial();
    EXPECT_THAT(sut
		.goTo("B", 24)
		.goTo("C", 24)
		.position(),
		Eq("C")); // Player with largest Valve id is handled
			  // first. Only care about that order is well
			  // defined which it has to be since set is sorted
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
  auto const sut = StateA::initial({"JJ","DD"}).goTo("JJ", 28, 20);
  EXPECT_THAT(sut.position(), Eq("JJ"));
  EXPECT_THAT(sut.timeLeft(), Eq(28));
  EXPECT_THAT(sut.flow().value(), Eq(28*20));

  EXPECT_FALSE(sut.notVisited().contains("JJ"));
  EXPECT_TRUE(sut.notVisited().contains("DD"));
}

TEST(forEachPath, do_nothing_if_remaining_time_is_less_than_one)
{
  bool called{false};

  std::function<void(Flow)> callback = [&called](Flow f){called=true;};
  forEachPath(callback,
	      example<Topology>(),
	      StateA("",
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
	      StateA("",
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

TEST(SolB, example)
{
  EXPECT_THAT(SolB(example<Topology>()), Eq(1707));
}


TEST(DISABLED_SolA, input)
{
  std::ifstream in(INPUT);
  EXPECT_THAT(SolA(Topology(in)), Eq(1720));
}

TEST(DISABLED_SolB, input)
{
  std::ifstream in(INPUT);
  auto ret = SolB(Topology(in));
  EXPECT_THAT(ret, Gt(2389));
}


