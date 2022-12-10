#pragma once

class Tree{
  char value_;
  bool ticked_{false};
public:
  Tree(char c);
  Tree(Tree const & t);
  
  bool ticked() const;
  char value()  const;
  void tick();
};
