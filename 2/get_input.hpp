#pragma once
#include<string>
#include"rule_and_password.hpp"
#include<vector>
using namespace std;

vector<RuleAndPassword> example_input()
{
  return {
    {Rule{1,3,'a'}, "abcde"},
    {Rule{1,3,'b'}, "cdefg"},
    {Rule{2,9,'c'}, "ccccccccc"}};
}
