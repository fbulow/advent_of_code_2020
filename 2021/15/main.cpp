#include <gtest/gtest.h>
#include <ranges>

#include "input.hpp"
#include "test.hpp"
#include "solution.hpp"
#include "cost.hpp"

auto solution_a(Data const &cav)
{
  Cost cost(cav);
  auto ans = travel_south_east(cav, cost);
  while(ans != travel_south_east(cav, cost))
    ans = travel_south_east(cav, cost);
  return cost.bottomRight().value();
}

auto solution_b(Data in)
{
  auto cav = five(in);
  Cost cost(cav);
  auto a = travel_south_east(cav, cost);
  auto b = travel_south_east(cav, cost);
  cout<<a<<endl<<b;

  while(a!=b)
    {
      a=b;
      b=travel_south_east(cav, cost);
      cout<<b<< " " <<cost.bottomRight().value()<<endl;
    }
  
  
  return cost.bottomRight().value();
}

TEST(solutionb, example)
{
  EXPECT_EQ(315, solution_b(example()));
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

      auto b = solution_b(data);
      assert(b > 2199);
      
      cout<<"a: "<<solution_a(data)<<endl
          <<"b: "<<b<<endl;
    }
}

