#pragma once
#include "snalifish.hpp"
using namespace std;

using Data = string;
Data input(istream& cin)
{
  Data ret;
  getline(cin, ret);
  return ret;
}

TEST(input, all)
{
  istringstream in("Hello world");
  EXPECT_EQ("Hello world", input(in));
}

