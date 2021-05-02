#pragma once
#include <vector>

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
    
  vector<Distance> data;
public:
  void add_distance(char from, char to, Steps distance);
  Steps get_distance( char from, char to );
};
