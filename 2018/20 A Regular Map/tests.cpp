#include <gtest/gtest.h>
#include "main.cpp"
#include <fstream>
#include <sstream>
#include "doors.hpp"
#include "trail.hpp"
#include "transverse.hpp"
#include "max_distance.hpp"

TEST(minSteps, empty)
{
  ASSERT_EQ(0, minSteps("$^"));
}

TEST(minSteps, one)
{
  ASSERT_EQ(1, minSteps("^N$"));
}

TEST(minSteps, one_paren)
{
  ASSERT_EQ(1, minSteps("^(N|)$"));
}

TEST(minSteps, fcn_as_argument)
{
  auto fcn = []()
  {
    static int i=0;
    switch(i++)
      {
      case 0:
        return '^';
      case 1:
        return 'N';
      case 2:
        return '$';
      }
    return '\n';
  };
  
  EXPECT_EQ(1, minSteps(fcn,0));
}

TEST(doors, initial_ab)
{
  Doors sut;
  auto const a = Position{0,0};

  sut.push(a, a.step('N'));
    
  EXPECT_EQ(sut.pop(a)[0],
            a.step('N'));
}

TEST(doors, initial_ba)
{
  Doors sut;
  auto const a = Position{0,0};

  sut.push(a, a.step('N'));
    
  EXPECT_EQ(sut.pop(a.step('N'))[0],
            a);
}

TEST(doors, pop_erases)
{
  Doors sut;
  auto const a = Position{0,0};

  sut.push(a, a.step('N'));
    
  EXPECT_EQ(1, sut.pop(a).size());//Popped here...
  EXPECT_EQ(0, sut.pop(a).size());//gone here
}

TEST(doors, pop_erases_second_element)
{
  Doors sut;
  auto const a = Position{0,0};

  sut.push(a, a.step('N'));
    
  EXPECT_EQ(1, sut.pop(a.step('N')).size());//Popped here...
  EXPECT_EQ(0, sut.pop(a.step('N')).size());//gone here
}

TEST(doors, get_multiple)
{
  Doors sut;
  auto const a = Position{0,0};

  sut.push(a, a.step('N'));
  sut.push(a, a.step('S'));
    
  EXPECT_EQ(2, sut.pop(a).size());//Popped here...
}

TEST(doors, start_empty)
{
  Doors sut;
  ASSERT_EQ(0, sut.pop(Position{0,0}).size());
}

TEST(doors, push_single_multiple_times)
{
  Doors sut;
  auto const a = Position{0,0};

  sut.push(a, a.step('N'));
  sut.push(a, a.step('N'));
    
  EXPECT_EQ(1, sut.pop(a).size());
}

TEST(trail, one_move)
{
  Trail sut;
  sut.step('N');
  EXPECT_EQ(1, sut.d.pop(Position{0,0}).size());
}

TEST(transverse_ignore_branching, plain_sequence)
{
  istringstream in("^N(W$S");
  ostringstream out;
  transverse_ignore_branching(in,
            [&out](char c)
            {
              out.put(c);
            });
  ASSERT_EQ("NW", out.str());
}

TEST(max_distance, zero)
{
  Doors sut;
  EXPECT_EQ(Distance(0), 
            max_distance(sut));
}

TEST(max_distance, one)
{
  Doors sut;
  Position p{0,0};
  sut.push(p, p.step('N'));
  EXPECT_EQ(Distance{1}, 
            max_distance(sut));
}

Distance solutionA(istream& in)
{
  Trail t;
  transverse_ignore_branching(in,
                              [&t](char c)
                              {
                                t.step(c);
                              });
  return max_distance(t.d);
}

Distance solutionA(std::string s)
{
  istringstream in(s);
  return solutionA(in);
}

TEST(examples, all)
{
    // In the first example (^WNE$), this would be the north-east corner 3 doors away.
  EXPECT_EQ(3, value_of(solutionA("^WNE$")));
    // In the second example (^ENWWW(NEEE|SSE(EE|N))$), this would be the south-east corner 10 doors away.
  EXPECT_EQ(10, value_of(solutionA("^ENWWW(NEEE|SSE(EE|N))$")));
  // In the third example (^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$), this would be the north-east corner 18 doors away.

  //EXPECT_EQ(18, minSteps("^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$"));

}

TEST(examples, substr)
{
  EXPECT_EQ(10, minSteps("^(WNSE|)EE(SWEN|)$"));
  //EXPECT_EQ(6, minSteps("^EE(SWEN|)$"));
  //  EXPECT_EQ(6, minSteps("^(WNSE|)EE$"));
                           
}

