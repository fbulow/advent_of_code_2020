#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cassert>
#include "node.hh"
#include <sstream>
#include <fstream>
#include "compare.hh"

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


struct LeftAndRight{
  Node left;
  Node right;
};


auto getData(auto filename)
{
  std::vector<LeftAndRight> ret;
  if(ret.empty())
    {
      ret.reserve(100);
      ifstream in(filename);
      try{
	while(true)
	  ret.emplace_back(LeftAndRight({in}, {in}));
      }catch(...)
	{}
    }
  return ret;
}

auto example()
{
  return getData(EXAMPLE);
}
LeftAndRight example(size_t i)
{
  return example()[i];
}

int solutionA(vector<LeftAndRight> const &data)
{
  int ret{0};
  for(auto i =0; i<data.size(); i++)
    if(compare(data[i].left, data[i].right)==Compare::Right)
      ret+=(i+1);
  return ret;
}

TEST(solutionA, input)
{
  EXPECT_THAT(solutionA(getData(INPUT)), Eq(6272));
}


TEST(solutionA, example)
{
  EXPECT_THAT(solutionA(example()), Eq(13));
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
TEST(example, six)
{
    auto x = example(5);
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
