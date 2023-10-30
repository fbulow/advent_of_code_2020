#include "for_each_path.hh"
#include"include.hh"

TEST(score, eval)
{
  auto input = example();
  EXPECT_THAT( 
	      Score()
	      .log(2 , input.flow("DD"))
	      .log(5 , input.flow("BB"))
	      .log(9 , input.flow("JJ"))
	      .log(17, input.flow("HH"))
	      .log(21, input.flow("EE"))
	      .log(24, input.flow("CC"))
	      .total(),
	      Eq(1651));
}

TEST(distance, example)
{
  EXPECT_THAT(distance(example(), "AA", "DD"),
	      Eq(1));
  EXPECT_THAT(distance(example(), "AA", "CC"),
	      Eq(2));
  EXPECT_THAT(distance(example(), "CC", "AA" ),
	      Eq(2));
}

TEST(ValveConnection, from_is_less_than_to_right_order_in_ctor)
{
  ValveConnection const sut("AA", "BB", 55);
  EXPECT_THAT(sut.from (), Eq("AA"));
  EXPECT_THAT(sut.to   (), Eq("BB"));
  EXPECT_THAT(sut.steps(), Eq(55));
  
}

TEST(ValveConnection, from_is_less_than_to_wrong_order_in_ctor)
{
  ValveConnection const sut("BB", "AA", 55);
  EXPECT_THAT(sut.from (), Eq("AA"));
  EXPECT_THAT(sut.to   (), Eq("BB"));
  EXPECT_THAT(sut.steps(), Eq(55));
  
}

TEST(ValveConnection, less)
{
    ValveConnection a("BB", "AA", 55);
    ValveConnection b("BB", "AA", 55);
    EXPECT_FALSE(a<b);
    EXPECT_FALSE(b<a);
}

TEST(ValveConnection, not_same)
{
    ValveConnection a("BB", "AA", 55);
    ValveConnection b("BB", "A", 55);
    EXPECT_TRUE((a<b) || (b<a));
}

TEST(Path, exmaple)
{
  auto sut = Path().moveTo(1, "DD");
  EXPECT_THAT(sut.size(), Eq(1));
  EXPECT_THAT(sut[0].timePassed, Eq(2));
}

TEST(totalFlow, example_valves)
{
  Path p({
    {2,  "DD"},
    {5,  "BB"},
    {9,  "JJ"},
    {17, "HH"},
    {21, "EE"},
    {24, "CC"}});
  
  std::map<Valve, Flow> flowRates{
    {"AA", 0},
    {"BB", 13},
    {"CC", 2},
    {"DD", 20},
    {"EE", 3},
    {"FF", 0},
    {"GG", 0},
    {"HH", 22},
    {"II", 0},
    {"JJ", 21}
  };

  EXPECT_THAT(totalVolume(p, flowRates),
	      1651);
  
}

TEST(SolA, zero_if_no_path)
{
  EXPECT_EQ(0,
	    SolA(
		 [](auto const&){return 5;},
		 [](PathCallback){}));
}

TEST(SolA, largest_value)
{
  EXPECT_EQ(5,
	    SolA(
		 [](Path const &p){
		   return p[0].timePassed;
		 },
		 [](PathCallback fcn)
		 {
		   fcn(Path({{1, ""}}));
		   fcn(Path({{5, ""}}));
		   fcn(Path({{2, ""}}));
		 }));
}



TEST(Regions, starts_as_outer)
{
  auto const ret  = Regions({"b", "c"}).outer();
  EXPECT_THAT(ret.size(), Eq(2));
  EXPECT_TRUE(ret.contains("b"));
  EXPECT_TRUE(ret.contains("c"));
}

TEST(Regions, starts_as_outer_start_at_b)
{
  auto const sut  = Regions({"b", "c"})
    .startAt("b");
  
  EXPECT_THAT(sut.edge().size(), Eq(1));
  EXPECT_TRUE(sut.edge().contains("b"));
  EXPECT_THAT(sut.outer().size(), Eq(1));
  EXPECT_TRUE(sut.outer().contains("c"));
}

TEST(pathIteration, isDone_no_regions_left)
{
  int callCount{0};
  pathIteration([&callCount](auto){callCount++;},
		0,
		[](auto, auto){return 1;},
		Regions ({"a"}).startAt("b"),
		Path().moveTo(0, "c"));
  EXPECT_THAT(callCount, Eq(1));
}

TEST(pathIteration, isDone_all_steps_are_too_long)
{
  int callCount{0};
  pathIteration([&callCount](auto){callCount++;},
		1,
		[](auto, auto){return 2;},
		Regions ({
		    "a",
		    "b",
		    "c"
		  }),
		"b"
		);
  EXPECT_THAT(callCount, Eq(1));
}

TEST(Path, moveTo_aa_distance_is_3_minutes_and_one_minute)
{
  auto sut = Path().moveTo(Minutes(3), "AA");
  EXPECT_THAT(sut.size(), 1);
  EXPECT_THAT(sut[0].open, Eq("AA"));
  EXPECT_THAT(sut[0].timePassed, Eq(4));//3+ one minute for opening the vault
}

TEST(Path, moveTo_aa_and_then_bb)
{
  auto sut = Path()
    .moveTo(Minutes(3), "AA")
    .moveTo(Minutes(2), "BB");
  EXPECT_THAT(sut.size(), 2);
  EXPECT_THAT(sut[1].open, Eq("BB"));
  EXPECT_THAT(sut[1].timePassed, Eq(7));//3+2+(2* one minute for opening the vault)
}

TEST(Regions, moveTo)
{
  auto const ret = 
  Regions({"a", "b", "c"})
    .startAt("a")
    .moveTo("b");

  EXPECT_THAT(ret.outer().size(), Eq(1));
  EXPECT_THAT(ret.edge().size(), Eq(1));
  EXPECT_THAT(ret.inner().size(), Eq(1));
  
}

TEST(pathIteration, can_go_to_a)
{
  /*  Possible paths {{1, b}} and {{2, a}}
   */
  std::vector<Path> vp;
  
  pathIteration([&vp](auto ret){vp.emplace_back(std::move(ret));},
		2,
		[](Valve a, Valve b){
		  if(a==b)
		    return 0;
		  if(((a=="b") and (b=="a"))
		     or
		     ((a=="a") and (b=="b")))
		    return 1;
		  else
		    return 2000;
		},
		Regions ({
		    "a",
		    "b",
		    "c"
		  }
		  ),
		"b");
  EXPECT_THAT(vp.size(), Eq(2));
}

TEST(pathIteration, just_move_to_a)
{
  std::vector<Path> vp;
  
  pathIteration([&vp](auto ret){vp.emplace_back(std::move(ret));},
		2,
		[](Valve a, Valve b){
		  if(a==b)
		    return 0;
		  if(((a=="b") and (b=="a"))
		     or
		     ((a=="a") and (b=="b")))
		    return 1;
		  else
		    return 2000;
		},
		Regions ({
		    "a",
		    "b",
		    "c"
		  }).startAt("b"),
		Path());
  EXPECT_THAT(vp.size(), Eq(1));
  EXPECT_THAT(vp[0].size(), Eq(1));
  EXPECT_THAT(vp[0][0].open , Eq("a"));
  EXPECT_THAT(vp[0][0].timePassed , Eq(2));
}

TEST(Input, adjacent)
{
  auto const ref = Valves({"DD", "II", "BB"});
  EXPECT_EQ(example().adjacent("AA"), ref);
}

TEST(Input, nonzero)
{
  auto const ret = example().nonzero();
  EXPECT_TRUE (ret.contains("BB"));
  EXPECT_FALSE(ret.contains("GG"));
}

TEST(Regions, move_to_set_of_Valves)
{
  auto ret =
    Regions({"a", "b", "c", "d", "e", "f"})
    .startAt("a")
    .moveTos({"b", "c"});

  EXPECT_THAT(ret.inner().size(), Eq(1));
  EXPECT_THAT(ret.edge().size(),  Eq(2));
  EXPECT_THAT(ret.outer().size(), Eq(3));
}

TEST(floodFill, fromJJ)
{
  std::vector<std::tuple<Valve, Valve, Minutes>> data;
  floodFill([&data](Valve from , Valve to, Minutes distance){
    data.emplace_back(from, to, distance);
  },
    example(), // input 
    "JJ",
    1);
  
  ASSERT_THAT(data.size(), Eq(1));
  auto const& ret = data[0];
  EXPECT_THAT(std::get<0>(ret), Eq("JJ"));
  EXPECT_THAT(std::get<1>(ret), Eq("II"));
  EXPECT_THAT(std::get<2>(ret), Eq(1));
}    

TEST(floodFill, fromJJ_two_steps)
{
  bool passed = false;
  
  floodFill([&passed](Valve from, Valve to, Minutes duration){
    if((from=="JJ") && (to=="AA") && (duration == 2))
      passed=true;
      },
    example(), // Input 
    "JJ",
    2);
  EXPECT_TRUE(passed);
}    


TEST(floodFill, fromAA_one)
{
  int count{0};
  
  floodFill([&count](Valve from, Valve to, Minutes duration){
    count++;
      },
    example(), // Input 
    "AA",
    1);
  EXPECT_THAT(count, Eq(3));
}    
