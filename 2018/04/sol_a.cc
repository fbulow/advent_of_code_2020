#include "notes.hh"
#include "simulation.hh"
#include <map>
#include <algorithm>
#include <fstream>
#include <array>
#include <numeric>

class Sleepogram
{
  std::array<int,60> data;
  public:
  Sleepogram()
  {
    for(auto &x:data)
      x=0;
  }
  void add(int minute)
  {
    assert(minute>=0);
    assert(minute<60);
    data[minute]++;
  }

  int total() const
  {
    return std::accumulate(data.cbegin(),
			   data.cend(), 0);
  }
  int sleepiestMinute() const
  {
    return distance(data.cbegin(), max_element(data.cbegin(),
					       data.cend()));
		
  }
  std::string view() const{
    std::string ret;
    ret.resize(60);
    transform(data.cbegin(),
	      data.cend(),
	      ret.begin(),
	      [](auto count)
	      {if(count)
		  return '#';
		else
		  return '.';
	      });
    return ret;
  }
};

auto sleepiestGuard(Notes const &n)
{
  map<int, Sleepogram> guardToMinutesAsleep;
  Simulation s(*n.cbegin(),
	       [&guardToMinutesAsleep](Guard guard, int minute)
	       {
		   guardToMinutesAsleep[guard.get()].add(minute);
	       }
	       );
  for_each(next(n.cbegin()),
	   n.cend(),
	   [&s](Note const &note)
	   {
	     s.execute(note);
	   });

  
  
  return max_element(guardToMinutesAsleep.cbegin(),
		     guardToMinutesAsleep.cend(),
		     [](auto const& lhs, auto const& rhs)
		     {
		       return lhs.second.total() < rhs.second.total();
		     });
}

int solA(Notes const &n)
{
  auto guard = sleepiestGuard(n);
  return guard->first * guard->second.sleepiestMinute();
}

#include "simulation.hh"
#include<sstream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(example, times_of_ten)
{
  Sleepogram s;
  Simulation sut("[1518-11-01 00:00] Guard #10 begins shift",
		 [&s](Guard, int minute)
		 {
		   s.add(minute);
		 });
  sut.execute("[1518-11-01 00:05] falls asleep\n");
  sut.execute("[1518-11-01 00:25] wakes up\n");
  sut.execute("[1518-11-01 00:30] falls asleep\n");
  sut.execute("[1518-11-01 00:55] wakes up\n");
  EXPECT_THAT(s.view(), Eq(".....####################.....#########################....."));
}

TEST(example, times_of_ten_two)
{
  Sleepogram s;
  Simulation sut("[1518-11-03 00:05] Guard #10 begins shift",
		 [&s](Guard, int minute)
		 {
		     s.add(minute);
		 });
  sut.execute("[1518-11-03 00:24] falls asleep");
  sut.execute("[1518-11-03 00:29] wakes up");
  EXPECT_THAT(s.view(), Eq("........................#####..............................."));
}


TEST(a, example)
{
  istringstream in(
		   "[1518-11-01 00:00] Guard #10 begins shift\n"
		   "[1518-11-01 00:05] falls asleep\n"
		   "[1518-11-01 00:25] wakes up\n"
		   "[1518-11-01 00:30] falls asleep\n"
		   "[1518-11-01 00:55] wakes up\n"
		   "[1518-11-01 23:58] Guard #99 begins shift\n"
		   "[1518-11-02 00:40] falls asleep\n"
		   "[1518-11-02 00:50] wakes up\n"
		   "[1518-11-03 00:05] Guard #10 begins shift\n"
		   "[1518-11-03 00:24] falls asleep\n"
		   "[1518-11-03 00:29] wakes up\n"
		   "[1518-11-04 00:02] Guard #99 begins shift\n"
		   "[1518-11-04 00:36] falls asleep\n"
		   "[1518-11-04 00:46] wakes up\n"
		   "[1518-11-05 00:03] Guard #99 begins shift\n"
		   "[1518-11-05 00:45] falls asleep\n"
		   "[1518-11-05 00:55] wakes up\n");
  Notes n;
  in>>n;

  auto guard = sleepiestGuard(n);
  ASSERT_THAT(guard->first, Eq(10));
  ASSERT_THAT(guard->second.sleepiestMinute(), Eq(24));
  ASSERT_THAT(solA(n), Eq(240));
    
}

TEST(DISABLED_a, acutal)
{
  ifstream in(INPUT);
  Notes n;
  in>>n;
  ASSERT_THAT(n.size(), Eq(1102));
  auto ans = solA(n);
  ASSERT_THAT(ans, Lt(30857));
  cout<<"Ans A: "<<ans<<endl;

}
