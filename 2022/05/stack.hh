#pragma once
#include <vector>



class Stack{
  std::vector<char> data ;
public:
  char top() const;

  Stack& push_bottom(char c);
  Stack& push_top(char c);
  char pop();
};
