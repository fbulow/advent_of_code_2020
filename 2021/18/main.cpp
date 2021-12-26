#include <variant>
#include<sstream>
#include <gtest/gtest.h>
#include <memory>
#include "strong_type.hpp"
using namespace std;

#include "input.hpp"
#include "test.hpp"
#include "solution.hpp"

auto solution_a(Data const &in)
{
  return "";
}

auto solution_b(Data in)
{
  return "";
}


int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  if(ret!=0)
    return ret;
  else
    {
      ifstream in(INPUT);
      auto data = input(in);
      cout<<"a: "<<solution_a(data)<<endl
          <<"b: "<<solution_b(data)<<endl;
    }
}

