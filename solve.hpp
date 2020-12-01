#pragma once
#include<vector>
#include<optional>
using namespace std;



std::optional<int> solve(vector<int> input, int pick = 2, int magic_number=2020)
{
  auto first = input.begin();
  while(first != input.end())
    {
      auto other = std::find_if(first,
				input.end(),
				[first, magic_number](auto x){return x+(*first) == magic_number;});
      if(other==input.end())
	first++;
      else
	return (*first)*(*other);
    }
  return {};
}
