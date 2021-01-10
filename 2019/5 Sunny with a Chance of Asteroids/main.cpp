#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
#include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
#include <functional>
#include <boost/algorithm/string.hpp> 
#include <boost/algorithm/string/join.hpp>
#include "intcode.hpp"
I solutionA(string filename)
{
  IntCode sut((ifstream(filename)));
  sut.input.push(1);
  while(sut.step())
    {}

  auto ret = sut.output.front();
  while(not sut.output.empty())
    {
      assert(0==ret);
      ret = sut.output.front();
      sut.output.pop();
    }
  return ret;
}
