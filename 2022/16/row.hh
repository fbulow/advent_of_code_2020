#pragma once
#include <string>
#include <vector>

using namespace std;

struct Row{
  std::string from;
  int rate{1};
  vector<std::string> to;
  Row(std::string row);
};
