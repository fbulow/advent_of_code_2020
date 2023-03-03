#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cassert>
#include "node.hh"
#include <sstream>
#include <fstream>

using namespace testing;
using namespace std;

ostream& operator<<(ostream& out, Compare c)
{
  switch(c)
    {
    case Compare::Right:
      return out << "Right";
    case Compare::Wrong:
      return out << "Wrong";
    case Compare::Equal:
      return out << "Equal";
    }
  return out<<"ERROR";
}

Compare compare(Int lhs, Int rhs)
{
  if (lhs<rhs)
    return Compare::Right;
  else if (lhs==rhs)
    return Compare::Equal;
  else
    return Compare::Wrong;
}

Compare compare(Node const &lhs, Node const &rhs)
{
  if(lhs.isInteger() and rhs.isInteger())
    return compare(lhs.getInt(), rhs.getInt());
  else if ((not lhs.isInteger()) and (not rhs.isInteger()))
    {
      auto a = lhs.cbegin();
      auto b = rhs.cbegin();

      auto ret = compare(*a, *b);
      while(ret == Compare::Equal)
	{
	  a++;
	  b++;
	  if(a==lhs.cend())
	    return b==rhs.cend()?Compare::Equal : Compare::Right;
	  else if (b==rhs.cend())
	    return Compare::Wrong;
	  ret = compare(*a, *b);
	}
      return ret;
    }
  else if (lhs.isInteger())
    return compare(lhs.asList(), rhs);
  else
    {
      return compare(lhs, rhs.asList());
    }
}

struct LeftAndRight{
  Node left;
  Node right;
};

LeftAndRight example(size_t i)
  {
  static std::vector<LeftAndRight> ret;
  if(ret.empty())
    {
      ret.reserve(100);
      ifstream in(EXAMPLE);
      try{
	while(true)
	    ret.emplace_back(LeftAndRight({in}, {in}));
      }catch(...)
	{}
    }
  return ret[i];
}


TEST(example, first)
{
    auto x = example(0);
    EXPECT_THAT(compare(x.left, x.right), Eq(Compare::Right));
    EXPECT_THAT(compare(x.right, x.left), Eq(Compare::Wrong));
}

TEST(example, second)
{
    auto x = example(1);
    EXPECT_THAT(compare(x.left, x.right), Eq(Compare::Right));
    EXPECT_THAT(compare(x.right, x.left), Eq(Compare::Wrong));
}
TEST(example, third)
{
    auto x = example(2);
    EXPECT_THAT(compare(x.left, x.right), Eq(Compare::Wrong));
    EXPECT_THAT(compare(x.right, x.left), Eq(Compare::Right));
}
TEST(example, fourth)
{
    auto x = example(3);
    EXPECT_THAT(compare(x.left, x.right), Eq(Compare::Right));
    EXPECT_THAT(compare(x.right, x.left), Eq(Compare::Wrong));
}


TEST(Node, toList)
{
  Node n(1);
  auto sut = n.asList();
  EXPECT_THAT(sut[0].getInt(), Eq(1));
}

TEST(Read, a_list_of_numbers_and_a_list)
{
  istringstream in("[0,[2,3],4]");
  Node sut(in);
  EXPECT_FALSE(sut.empty());
  EXPECT_THAT(sut.size(), Eq(3));

  EXPECT_THAT(sut[0].getInt(), Eq(0));
  EXPECT_THAT(sut[2].getInt(), Eq(4));
}

TEST(Read, a_list_of_numbers)
{
  istringstream in("[1,2,3,4]");
  Node sut(in);
  EXPECT_FALSE(sut.empty());
  EXPECT_THAT(sut[0].getInt(), Eq(1));
  EXPECT_THAT(sut[1].getInt(), Eq(2));
  EXPECT_THAT(sut[2].getInt(), Eq(3));
  EXPECT_THAT(sut[3].getInt(), Eq(4));
}


TEST(Node, is_Int)
{
  Node sut(1);
  EXPECT_TRUE(sut.isInteger());
  EXPECT_THAT(sut.getInt(), Eq(1));
}
TEST(Node, is_list)
{
  auto sut = Node();
  EXPECT_FALSE(sut.isInteger());
  EXPECT_TRUE(sut.empty());
  sut.push(1);
  EXPECT_FALSE(sut.empty());
}
