#pragma once
#include <string>
#include <vector>

using namespace std;

struct Row{
  std::string from;
  vector<std::string> to;
  int rate{1};
  static Row fromString(std::string row);
};
