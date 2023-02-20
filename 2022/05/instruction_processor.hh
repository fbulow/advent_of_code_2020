#pragma once
#include <vector>
#include <string>
class Stack;

class InstructionProcessor{
  std::vector<Stack> data;
protected:
  char pop(std::size_t crate);
  void push(std::size_t crate, char value);
  
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
