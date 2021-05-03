#pragma once
#include <vector>
#include <optional>
#include <forward_list> 
using namespace std;

class DistanceTable{
public:
  using Steps = unsigned int;
private:
  struct Distance{
    char from;
    char to;
    Steps steps;
    Distance( char from,
              char to,
              Steps steps)
      :from{min(to,from)}
      ,to{max(to,from)}
      ,steps{steps}
    {}
      
};
    
  forward_list<Distance> data;
public:
  void add_distance(char from, char to, Steps distance);
  Steps get_distance( char from, char to );
  void remove(char c);

  using Nodes=vector<pair<char, Steps>>;
  Nodes get_nodes(char) const;
};
