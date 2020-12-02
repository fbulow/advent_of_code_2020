#pragma once
#include<vector>
#include<optional>
using namespace std;

optional<int> solve(vector<int>::iterator, 
		    vector<int>::iterator, 
		    int pick = 2, int magic_number=2020);

inline optional<int> solve(vector<int> input, int pick = 2, int magic_number=2020)
{
  return solve(input.begin(), input.end(), pick, magic_number);
}
