#pragma once
#include <string>
#include <istream>
struct Rule{
  int min;
  int max;
  char letter;
};

using Password=std::string;

struct RuleAndPassword{
  Rule rule;
  Password password;
};

