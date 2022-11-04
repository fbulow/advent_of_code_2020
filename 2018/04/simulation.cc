#include "simulation.hh"
#include<sstream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(Simulation, guard_is_asleep_at_end_of_shift)
{
  int count{0};
  Simulation sut("[1518-11-01 00:00] Guard #10 begins shift",
		 [&count](Guard, Time const & )
		 {
		   count++;
		 });
  sut.execute("[1518-11-01 00:01] falls asleep");
  sut.execute("[1518-11-02 00:03] Guard #10 begins shift");

  EXPECT_THAT(count, Eq(62));  
}

TEST(Simulation, start_awake)
{
  int count{0};
  Simulation sut("[1518-11-01 00:00] Guard #10 begins shift",
		 [&count](Guard, Time const & )
		 {
		     count++;
		 });
  ASSERT_THAT(count, Eq(0));
  sut.execute("[1518-11-01 00:05] falls asleep\n");
  EXPECT_THAT(count, Eq(0));
}

TEST(Simulation, minute_overflow)
{
  Simulation sut("[1518-03-31 23:49] Guard #151 begins shift");
  sut.execute("[1518-04-01 00:03] falls asleep");
}


TEST(Simulation, callback_second_guard_shows_up)
{
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"));
  EXPECT_THAT(sut.guard().get(), Eq(10));
  sut.execute(Note("[1518-11-02 00:00] Guard #11 begins shift"));
  EXPECT_THAT(sut.guard().get(), Eq(11));
}

TEST(Simulation, callback_fall_asleep_and_wake_up)
{
  int awake{0};
  int asleep{0};
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"),
		 [&awake, &asleep](Guard, Time const &){
		     asleep++;
		 });
  sut.execute(Note("[1518-11-01 00:05] falls asleep"));
  sut.execute(Note("[1518-11-01 00:07] wakes up"));

  EXPECT_THAT(asleep, Eq(2));
}

TEST(Simulation, execute_awake)
{
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"));
  EXPECT_TRUE(sut.awake());
  sut.execute(Note("[1518-11-01 00:05] falls asleep"));
  EXPECT_FALSE(sut.awake());
  sut.execute(Note("[1518-11-01 00:25] wakes up"));
  EXPECT_TRUE(sut.awake());
}


TEST(Simulation, initialize)
{
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"));
  EXPECT_THAT(sut.time(), Eq(Time(1518,11,01,00,00)));
  EXPECT_TRUE(sut.awake());
}
