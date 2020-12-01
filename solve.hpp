#pragma once
#include<vector>
using namespace std;
int solve(vector<int> input)
{
  auto first = input.begin();
  while(first != input.end())
    {
      auto other = std::find_if(first, input.end(), [first](auto x){return x+(*first) == 2020;});
      if(other==input.end())
	first++;
      else
	return (*first)*(*other);
    }
  throw std::exception{};
}
