#pragma once
#include <vector>
#include <set>
using namespace std;

inline
int firstRepeating(vector<int> const &data, set<int>& visited, int sum, size_t index)
{
  if(visited.contains(sum))
    return sum;
  else
    {
      visited.insert(sum);
      index%=data.size();
      return firstRepeating(data, visited, sum+=data[index], index+1);
    }
  

}

inline
int firstRepeating(vector<int> const &data)
{
  set<int> visited;
  return firstRepeating(data, visited, 0, 0);
}
  
