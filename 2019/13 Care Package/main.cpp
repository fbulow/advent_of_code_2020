#include <fstream>
#include <string>
//#include <vector>
//#include <cmath>
//#include <iostream>
//#include <ranges>
//// #include <limits>
//#include <numeric>
#include <cassert>
//#include<list>
//#include<deque>
//#include <initializer_list>
//#include <functional>
//#include <boost/algorithm/string.hpp> 
//#include <boost/algorithm/string/join.hpp>
#include "intcode.hpp"
#include <set>

using namespace std;


I solutionA(string filename)
{
  IntCode computer((ifstream(filename)));
  set<array<long long int,3>> board;
  computer.run();
  auto &o = computer.output;
  auto nxt = [&o](){
    assert(not o.empty());
    auto ret = o.front();
    o.pop();
    return ret;
  };
  while(not computer.output.empty())
    board.insert({nxt(),nxt(),nxt()});

  return count_if(board.begin(), board.end(), [](auto const&x){return x[2]==2;});
  
}



