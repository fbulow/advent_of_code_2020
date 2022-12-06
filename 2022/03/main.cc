#include <AoC/getAllLines.hh>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>
#include <ranges>
#include <iterator>
#include <string_view>
#include <map>
#include "row.hh"


using namespace std;


int priority(char c);

int sumUp(string const &s)
{
  return accumulate(s.begin(), s.end(),
		    int(0),
		    [](int ret, char nxt)
		    {
		      return ret+priority(nxt);
		    });
}
  

int priority(char c)
{
  
  // Lowercase item types a through z have priorities 1 through 26.
  // Uppercase item types A through Z have priorities 27 through 52.
  if(c<='Z')
    return c-'A'+27;
  else
    return c-'a'+1;
}

set<char> firstHalf(string const & line)
{
  auto middle = next(line.begin(),
		     line.size()/2);

  return {line.begin(), middle};
  
}

string commonLetters(vector<string> const & lines)
{
  string ret;
  for(auto & line:lines)
    {
      if(line.size()>0)
	{
	  auto firstCompartment = firstHalf(line);
	  
	  auto middle = next(line.begin(),
			     line.size()/2);

	  while(not firstCompartment.contains(*middle))
	    {
	      advance(middle,1);
	      if (middle>=line.end())
		break;
	    }
	  ret.push_back(*middle);
	}
    }
  
  return ret;
}

int solA(auto const &data)
{
  return sumUp(commonLetters(data));
}

using OptBadge = std::optional<char>;
struct  Rucksack : set<char>
{
  string original;
  Rucksack()
    :set<char>()
  {}

  Rucksack(char const *s)
    :Rucksack(string_view(s))
  {}
    
  Rucksack(string_view s)
    :original(s)
  {
    ranges::copy_if(s, inserter(*this, end()), [](auto c){return c!=0;});
  }
};

OptBadge badge(Rucksack const &a,
	       Rucksack const &b,
	       Rucksack const &c)
{
  Rucksack ab;
  ranges::set_intersection(a,
			   b, inserter(ab,ab.end()));
  Rucksack abc;
  ranges::set_intersection(ab,c, inserter(abc, abc.end()));
  if(abc.size()==1)
    return *abc.begin();
  else
    return {};
}

class Group: public array<RowNr, 3>
{
public:
  Group(RowNr a, RowNr b, RowNr c)
    :array<RowNr, 3>{a,b,c}
  {
    assert(a!=b);
    assert(a!=c);
    assert(b!=c);
  }

  bool contains(RowNr nr) const
  {
    return any_of(begin(), end(), [nr](auto x){return x==nr;});
  }
};

struct Groups:vector<Group>
{
  unsigned int count(RowNr nr) const
  {
    return count_if(begin(),
		    end(),
		    [nr](auto const & group)
		    {
		      return group.contains(nr);
		    });
  }
};

struct BadgeToGroups:map<char, Groups>
{
  
  BadgeToGroups (vector<Rucksack> const &allRucksacks)
  {
    size_t const end = allRucksacks.size();

  for(RowNr a=0;
      a < end-2;
      a++)
    for(RowNr b = a+1;
	b < end-1;
	b++)
      for(RowNr c = b+1;
	  c < end;
	  c++)
	{
	  auto itIsAGroup = badge(allRucksacks[a],
				  allRucksacks[b],
				  allRucksacks[c]);
	  if(itIsAGroup)
	    (*this)[itIsAGroup.value()]
	      .emplace_back(Group{a,b,c});
	}
  }

  void removeAllRow(RowNr nr)
  {
    for(pair<const char, Groups> &charAndGroups: *this)
      {
	auto groupIt = charAndGroups.second.begin();
	while(groupIt<charAndGroups.second.end())
	  if(groupIt->contains(nr))
	    groupIt=charAndGroups.second.erase(groupIt);
	  else
	    groupIt++;
      }
  }
  
  unsigned int countGroupsWithRow(RowNr nr) const
  {
    return accumulate(begin(),
		      end(),
		      uint(0),
		      [nr](unsigned int summa, auto const& char_and_groups)
		      {
			return summa+char_and_groups.second.count(nr);
		      });
  }
};
  




#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(countGroupsWithRow, example)
{
  auto sut = BadgeToGroups(getAllLines<Rucksack>(EXAMPLE));
  ASSERT_THAT(sut.countGroupsWithRow(5)
	      ,Gt(0));
  sut.removeAllRow(5);
  EXPECT_THAT(sut.countGroupsWithRow(5)
	      ,Eq(0));
  
}
  
TEST(Group, contains)
{
  auto sut = Group(1,2,3);
  EXPECT_TRUE (sut.contains(1));
  EXPECT_FALSE(sut.contains(4));
}


TEST(BadgeToGroups, cpy)
{
  auto sut = BadgeToGroups(getAllLines<Rucksack>(EXAMPLE));
  BadgeToGroups cpy = sut;
  ASSERT_EQ(1, sut['r'].size());
  ASSERT_EQ(2, sut['Z'].size());
}

TEST(BadgeToGroups, example)
{
  auto sut = BadgeToGroups(getAllLines<Rucksack>(EXAMPLE));

  ASSERT_EQ(1, sut['r'].size());
  ASSERT_EQ(2, sut['Z'].size());
}

TEST(badge, two_common)
{
  auto sut = badge("ade","bde","cde");
  EXPECT_FALSE(sut);
}

TEST(badge, example_1)
{


  auto sut = badge(
		   "vJrwpWtwJgWrhcsFMMfFFhFp",
		   "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
		   "PmmdzqPrVvPwwTWBwg");
  EXPECT_TRUE(sut);
  EXPECT_EQ('r', sut.value());
}

TEST(solA, real)
{
  EXPECT_EQ(7826, solA(getAllLines()));
}

TEST(solA, example)
{
  istringstream in(
		   R""(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)"");


  EXPECT_EQ(157, solA(getAllLines(in)));
}


TEST(sumUp, example)
{
  EXPECT_EQ(157, sumUp("pLPvts"));
}

TEST(priority, all)
{
  // Lowercase item types a through z have priorities 1 through 26.
  // Uppercase item types A through Z have priorities 27 through 52.

  EXPECT_EQ(1, priority('a'));
  EXPECT_EQ(27, priority('A'));

  EXPECT_EQ(16, priority('p'));
  EXPECT_EQ(38, priority('L'));
  EXPECT_EQ(42, priority('P'));
  EXPECT_EQ(22, priority('v'));
  EXPECT_EQ(20, priority('t'));
  EXPECT_EQ(19, priority('s'));
  
}


TEST(firstHalf, all)
{
  auto sut = firstHalf("abcd");
  ASSERT_THAT(sut.size(), Eq(2));
  ASSERT_TRUE(sut.contains('a'));
  ASSERT_TRUE(sut.contains('b'));
  ASSERT_FALSE(sut.contains('c'));
  ASSERT_FALSE(sut.contains('d'));
    
}
TEST(commonLetters, vJrwpWtwJgWrhcsFMMfFFhFp)
{
  vector<string> sut{"vJrwpWtwJgWrhcsFMMfFFhFp"};
  EXPECT_THAT(commonLetters(sut), Eq("p"));
}


TEST(commonLetters, emptyToEmpty)
{
  vector<string> sut{""};
  EXPECT_THAT(commonLetters(sut), Eq(""));
}

TEST(commonLetters, aa)
{
  vector<string> sut{"aa"};
  EXPECT_THAT(commonLetters(sut), Eq("a"));
}

