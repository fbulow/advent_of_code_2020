#pragma once
#include <vector>
#include <string>
class Stack;

class InstructionProcessor{
  std::vector<Stack> data;
public:
  InstructionProcessor& applyRow(std::string const &s);
  std::string message() const;
};
