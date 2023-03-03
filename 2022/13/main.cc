#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <variant>
#include <list>
#include <sstream>
#include <cassert>

using namespace testing;
class Node;
using Int = int;
using NodeList = std::list<Node>;

class Node{
  std::variant<Int, std::list<Node>> data_;
public:
  Node():data_{std::list<Node>()}{}
  Node(Int i):data_(i){}
  Node(std::istream &in);

  Node const & operator[] (size_t i) const
  {
    return *std::next(get<NodeList>(data_).begin(), i);
  }

  bool isInteger() const{return std::holds_alternative<Int>(data_);}
  Int getInt() const {return std::get<Int>(data_);}
  bool empty() const {return std::get<NodeList>(data_).empty();}
  Node& push(Node &&n) {return std::get<NodeList>(data_).emplace_back(std::move(n));return *this;}
  size_t size() const {return std::get<NodeList>(data_).size();}
  Node asList() const
  {
    auto clone = *this;
    auto ret = Node();
    ret.push(std::move(clone));
    return ret;
  }
};

using namespace std;


Node::Node(istream& in)
  :Node()
{
  char c;
  in>>c;
  while(c=='\n')
      in>>c;
  assert(c=='[');
  while(in.peek()!=']')
    {
      if(in.peek()=='[')
	push(Node(in));
      else
	{
	  Int val;
	  in>>val;
	  push({val});
	}
      if(in.peek()==',')
	in>>c;
    }
  in>>c;//absorb the ]
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
