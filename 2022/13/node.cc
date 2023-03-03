#include "node.hh"
#include <cassert>

Node::Node()
  :data_{std::list<Node>()}
{}

Node::Node(Int i):data_(i)
{}

Node::Node(std::istream &in)
  :Node()
{
  char c;
  in>>c;
  while(c=='\n')
      in>>c;
  if(in.eof())
    throw std::exception();
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

Node const & Node::operator[] (size_t i) const
  {
    return *std::next(get<NodeList>(data_).begin(), i);
  }

bool Node::isInteger() const{return std::holds_alternative<Int>(data_);}
Int Node::getInt() const {return std::get<Int>(data_);}
bool Node::empty() const {return std::get<NodeList>(data_).empty();}
Node& Node::push(Node &&n) {return std::get<NodeList>(data_).emplace_back(std::move(n));return *this;}
size_t Node::size() const {return std::get<NodeList>(data_).size();}

Node Node::asList() const
{
  auto clone = *this;
  auto ret = Node();
  ret.push(std::move(clone));
  return ret;
}

