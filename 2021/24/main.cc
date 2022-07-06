#include "input.hh"
#include <gtest/gtest.h>

TEST(solution, a)
{

  auto sut = State()
    .inp(7)
    .inp(9)
    .inp(1)
    .inp(9)
    .inp(7)
    .inp(9)
    .inp(1)
    .inp(9)
    .inp(9)
    .inp(9)
    .inp(3)
    .inp(9)
    .inp(8);
  //    .inp(5);

  
  
  EXPECT_EQ(0, sut.inp(5).z);//right
  EXPECT_NE(0, sut.inp(6).z);//wrong
  EXPECT_FALSE(sut.done());
  EXPECT_TRUE(sut.inp(5).done());
  EXPECT_TRUE(sut.inp(6).done());
}

#include<set>
using namespace std;
using Cache = set<std::array<Int,4>>;

bool solution_b(State const &s, auto cache_ptr)
{
  if(s.done())
    return s.pass();
  
  else if (cache_ptr->contains(s.data()))
    return false;
  else
    {
      for(auto i: {1,2,3,4,5,6,7,8,9})
	{
	  if(solution_b(s.inp(i), std::next(cache_ptr)))
	    {
	      std::cout<< i;
	      return true;
	    }
	}
      cache_ptr->insert(s.data());
      return false;
    }
}

void solution_b()
{
  array<Cache, 15> cache;
  std::cout<< std::endl;
  std::cout<< std::endl;
  solution_b(State(), cache.begin());
  std::cout<< std::endl;
  std::cout<< std::endl;
}

TEST(SOLUTION, b)
{
  solution_b();
}
