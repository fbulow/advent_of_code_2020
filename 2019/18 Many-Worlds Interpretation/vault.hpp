#pragma once

#include<vector> 
#include <string> 
using namespace std;

struct Destination
{
  char name;
};

class Vault{
public:
  Vault(vector<string> const & map)
  {}
  vector<Destination> destinations() const
  {return {Destination{'a'}};}
};
