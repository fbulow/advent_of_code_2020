#pragma once
#include <vector>
#include <string>
class Stack;

class InstructionProcessor{
protected:
  std::vector<Stack> data;
  virtual void moveCrates(int count, std::size_t from, std::size_t to);
    
public:
  InstructionProcessor& applyRow(std::string const &s);
  std::string message() const;
};


class CraneB : public InstructionProcessor
{
protected:
  void moveCrates(int count, std::size_t from, std::size_t to) override;
};
