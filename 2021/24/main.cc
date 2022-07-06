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

std::string solution_b(State const &s, auto cache_ptr)
{
  if (cache_ptr->contains(s.data()))
    return {};
  else
    {
      for(auto i: {1,2,3,4,5,6,7,8,9})
	{
	  auto t = s.inp(i);
	  if(t.done())
	    {
	      if(t.pass())
		{
		  std::string ret;
		  ret.push_back(char('0'+i));
		  return ret;
		}
	      else
		return {};
	    }
	  else
	    {
	      auto ret = solution_b(t, std::next(cache_ptr));
	      if(not ret.empty())
		{
		  ret.push_back(char('0'+i));
		  return ret;
		}
	    }
	}
      cache_ptr->insert(s.data());
      return {};
    }
}

void solution_b()
{
  array<Cache, 15> cache;
  std::string ret = solution_b(State(), cache.begin());
  std::reverse(ret.begin(), ret.end());
    
  std::cout<<ret<<std::endl;
  
}

TEST(SOLUTION, b)
{
  solution_b();
}
