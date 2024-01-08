
#include "impl.cc"

struct Row{
  string s;
  vector<int> g;
  Row(string const &row)
  {
    istringstream in(row);
    in>>s;
    int i;
    char comma;
    while(!(in>>i>>comma).fail())
      g.push_back(i);
    g.push_back(i);
  }
  long long int countArrangements() const
  {
    long long int ret{0};
    auto countIfOk =
      [&ret, this](string_view candidateRow)
      {
	if(isAMatch(s, candidateRow))
	  ret++;
      };
    forAllPermutations(countIfOk, s, g);
  }
};

auto solA(istream &&in)
{
  long long int ret{0};
  string s;
  while(getline(in, s))
    ret += Row(s).countArrangements();
  return ret;
}

/**/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(forAllPermutations, one_group_that_just_fits)
{
  int count{0};
  vector<int> g{};
  forAllPermutations([&count](auto s){count++;},
		     "...",
		     {3});
  EXPECT_THAT(count, Eq(1));
}


TEST(forAllPermutations, no_group_left_call_callback)
{
  int count{0};
  string s("");
  vector<int> g{};
  forAllPermutations([&count](){count++;},
		     s.begin(), s.end(),
		     g.begin(), g.end());
  EXPECT_THAT(count, Eq(1));
}

TEST(forAllPermutations, no_space_left_in_string_doNothing)
{
  int count{0};
  string s("");
  vector<int> g{1};
  forAllPermutations([&count](auto...){count++;},
		     s.begin(), s.end(),
		     g.begin(), g.end());
  EXPECT_THAT(count, Eq(0));
}

TEST(isAMatch, examples)
{
  EXPECT_TRUE(isAMatch('?', '?'));
  EXPECT_TRUE(isAMatch('#', '?'));
  EXPECT_TRUE(isAMatch('?', '#'));
  EXPECT_FALSE(isAMatch('#', '#'));
  EXPECT_TRUE(isAMatch('.', '#'));

  EXPECT_FALSE(isAMatch("##.", "#.."));
  EXPECT_TRUE(isAMatch(".?#", "#.."));
}


// TEST(Row, ctor)
// {
//   auto sut = Row("???.### 2,1,3");

//   sut.arr(sut.g.end(),
// 	  sut.s.begin())
	  
  
// }


TEST(Row, ctor)
{
  auto sut = Row("???.### 1,1,3");
  
  EXPECT_THAT(sut.s, Eq("???.###"));
  EXPECT_THAT(sut.g, ElementsAre(1,1,3));
}
