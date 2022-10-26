#include "simulation.hh"


TEST(Simulation, callback_fall_asleep_and_wake_up)
{
  int awake{0};
  int asleep{0};
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"),
		 [&awake, &asleep](int guard, bool isAwake){
		   if(isAwake)
		     awake++;
		   else
		     asleep++;
		 });
  sut.execute(Note("[1518-11-01 00:05] falls asleep"));
  sut.execute(Note("[1518-11-01 00:07] wakes up"));

  EXPECT_THAT(awake, Eq(5));
  EXPECT_THAT(asleep, Eq(2));
}

TEST(Simulation, callback)
{
  int a=0;
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"),
		 [&a](auto...){
		   a++;
		 });
  sut.execute(Note("[1518-11-01 00:05] falls asleep"));

  EXPECT_THAT(a, Eq(5));
}

TEST(Simulation, callback_guard_is_early)
{
  int a=0;
  Simulation sut(Note("[1518-11-01 23:45] Guard #10 begins shift"),
		 [&a](auto...){
		   a++;
		 });
  sut.execute(Note("[1518-11-02 00:05] falls asleep"));

  EXPECT_THAT(a, Eq(5));
}
TEST(Simulation, callback_guard_is_late)
{
  int a=0;
  Simulation sut(Note("[1518-11-02 00:03] Guard #10 begins shift"),
		 [&a](auto...){
		   a++;
		 });
  sut.execute(Note("[1518-11-02 00:05] falls asleep"));

  EXPECT_THAT(a, Eq(2));
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
