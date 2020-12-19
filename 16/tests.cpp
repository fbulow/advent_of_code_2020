#include <gtest/gtest.h>
#include "main.cpp"


TEST(a,a)
{
  MinMax sut{1,3};
  
  ASSERT_FALSE(sut.ok(0));
  ASSERT_TRUE (sut.ok(1));
  ASSERT_TRUE (sut.ok(2));
  ASSERT_TRUE (sut.ok(3));
  ASSERT_FALSE(sut.ok(4));
}

TEST(Rule, ctor)
{
  Rule sut("departure location: 29-766 or 786-950");
  EXPECT_EQ(29, sut.data[0].min);
  EXPECT_EQ(766, sut.data[0].max);
  EXPECT_EQ(786, sut.data[1].min);
  EXPECT_EQ(950, sut.data[1].max);
    
}

TEST(Ticket, ctor)
{
  Ticket sut("151,103");
  EXPECT_EQ(151, sut[0]);
  EXPECT_EQ(103, sut[1]);
  EXPECT_EQ(2, sut.size());
}

TEST(Rule, ok)
{
  Rule const sut(": 44-451 or 464-955");
  EXPECT_FALSE(sut.ok(43));
  EXPECT_TRUE(sut.ok(44));
  EXPECT_TRUE(sut.ok(45));
  EXPECT_TRUE(sut.ok(451));
  EXPECT_FALSE(sut.ok(452));
  EXPECT_FALSE(sut.ok(453));
  EXPECT_FALSE(sut.ok(463));
  EXPECT_TRUE(sut.ok(464));
  EXPECT_TRUE(sut.ok(465));

}

TEST(Input, read_rules)
{
  Input const sut(INPUT);
  EXPECT_EQ(20, sut.rules.size());
}



TEST(obviousInvalid, first)
{
  vector<Rule> sut{Rule(": 44-451 or 464-955"), Rule(": 2-5 or 7-9")};

  EXPECT_TRUE(obviousInvalid( 1, sut));

  EXPECT_FALSE(obviousInvalid( 4, sut));
}

TEST(scanningErrorRate, example)
{
  vector<Rule> const rules{
    Rule("class: 1-3 or 5-7"),
    Rule("row: 6-11 or 33-44"),
    Rule("seat: 13-40 or 45-50")};

  EXPECT_EQ(0,	Ticket ("7,3,47" ).scanningErrorRate(rules));
  EXPECT_EQ(4,	Ticket ("40,4,50").scanningErrorRate(rules));
  EXPECT_EQ(55, Ticket ("55,2,20").scanningErrorRate(rules));
  EXPECT_EQ(12, Ticket ("38,6,12").scanningErrorRate(rules));
  
}

TEST(solve, a)
{
  ASSERT_EQ(71, Input(EXAMPLE).ticketScanningErrorRate());
  
  auto ans = Input(INPUT).ticketScanningErrorRate();
  ASSERT_LT(ans, 1701758303);
  cout<<"Solution a: "<<ans<<endl;
  EXPECT_EQ(21980, ans);
}

TEST(rule, name)
{

  EXPECT_EQ("departure location",
	    Rule("departure location: 29-766 or 786-950").name);
}

TEST(answer, example)
{
  EXPECT_EQ(20,
	    answer({
		Rule("departure location: 29-766 or 786-950"),
		Rule("arrival station: 42-597 or 620-957")
	      }
	      ,{1,0},
	      Ticket ("10, 20")));
}

     
TEST(Conclude, values)
{
  Conclude const sut(EXAMPLE);
  EXPECT_EQ(Ticket("7,1,14"), sut.my);
  EXPECT_EQ(7, *sut.values[0].begin());

  auto secondElement = sut.values[1];
  EXPECT_TRUE(secondElement.contains(1));
  EXPECT_TRUE(secondElement.contains(3));
  EXPECT_FALSE(secondElement.contains(4));
}

TEST(Conclude, options)
{
  Conclude const sut(EXAMPLE);
  set<size_t> ref{0,1};
  EXPECT_EQ(ref, sut.options[0]);
}

TEST(uncertainty, cases)
{
  auto ans = uncertainty({set<size_t>{1,2}, set<size_t>{1}});
  EXPECT_EQ(3, ans);
}

TEST(solved, first)
{
  {
    auto ref = vector<Option>{Option{1},Option{2}};
    EXPECT_TRUE(solved(ref));
  }
  {
    auto ref = vector<Option>{Option{1,2},Option{2}};
    EXPECT_FALSE(solved(ref));
  }
  {
    auto ref = vector<Option>{Option{},Option{2}};
    EXPECT_FALSE(solved(ref));
  }
  {
    auto ref = vector<Option>{Option{2},Option{2}};
    EXPECT_FALSE(solved(ref));
  }

  
}
TEST(reduce_known, complete)
{
  auto ans = recursiveReduce({
      set<size_t>{1,2},
      set<size_t>{1},
      set<size_t>{2,3}});
  
  EXPECT_TRUE(solved(ans));
}




TEST(Conclude, show_input)
{
  Conclude sut(INPUT);

  //  sut.options=recursiveReduce(sut.options);
  
  for (auto x: sut.options)
    {
      cout<<"->  ";
      for(auto y: x)
	cout<<y<<", ";
      cout<<endl;
    }
}

