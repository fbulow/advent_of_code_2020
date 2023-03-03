#pragma once
#include <variant>
#include "types.hh"
#include <istream>

class Node{
  std::variant<Int, std::list<Node>> data_;
public:
  Node();
  Node(Int i);
  Node(std::istream &in);

  Node const & operator[] (size_t i) const;

  auto cbegin() const
  {
    return std::get<NodeList>(data_).cbegin();
  }
  auto cend() const
  {
    return std::get<NodeList>(data_).cend();
  }
  
  bool isInteger() const;
  Int getInt() const;
  bool empty() const;
  Node& push(Node &&n);
  size_t size() const;
  Node asList() const;
};




