#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <ctype.h>
#include <cmath>
#include <vector>
#include <cassert>

using namespace std;
using namespace testing;

using Int = int;

Int getInt(istream &in)
{
  static char slask;
  while(not (in.eof() or isdigit(in.peek()) or in.peek()=='-'))
    in>>slask;
  Int ret;
  in>>ret;
  return ret;
}



struct Sensor{
  Int x;
  Int y;
  Int r;
  Sensor(istream &in)
    :x{getInt(in)}
    ,y{getInt(in)}
    ,r{abs(getInt(in)-x)+abs(getInt(in)-y)}
  {
    if(in.eof())
      throw exception();
    assert(r>=0);
  }
};


vector<Sensor> getData(string filename)
{
  vector<Sensor> ret;
  ifstream in(filename);
  while(true)
      try{
	ret.emplace_back(Sensor(in));
      }catch(...){
	return ret;
      }
}

Int countOn(Int const activeSensors,
	    Int const startIndex,
	    auto const begin,
	    auto const end)
{
  if(begin==end)
    return 0;

  assert(activeSensors>=0);

  Int increase;
  if(activeSensors==0)
    increase = 0;
  else
    increase = ( begin->first - startIndex );

  
  return increase + countOn( activeSensors + begin->second,
			     begin->first,
			     next(begin),
			     end );
}

Int countOn(map<Int, int> const &onOff)
{
  auto start = onOff.begin();
  return  countOn(start->second,
		  start->first,
		  next(start),
		  onOff.end());
		  
}

Int beaconsOnRow(vector<Sensor> const &sensors, Int row)
{
  return count_if(sensors.begin(),
		  sensors.end(),
		  [row](auto const &s){
		    return s.x==row;
		  });
}

Int watchedLocationsCount(vector<Sensor> const &sensors, Int row)
{
  map<Int, int> onOff;
  for(auto const & s: sensors)
    {
      auto halfLength = s.r - abs(row-s.y);
      if( halfLength >=0 )
	{
	  onOff[s.x-halfLength  ]++; //Turn on
	  onOff[s.x+halfLength+1]--; //Turn off
	}
    }

  return countOn(onOff);
}

Int solutionA(string filename, Int row)
{
  return watchedLocationsCount(getData(filename), row)
    ;
}

TEST(solutionA, example)
{
  EXPECT_THAT(solutionA(EXAMPLE, 10), Eq(26));
}
     

TEST(getData, example)
{
  auto sut = *getData(EXAMPLE).rbegin();
  EXPECT_THAT(sut.x, Eq(20));
  EXPECT_THAT(sut.y, Eq(1));
}

TEST(read, example_dots)
{
  ifstream in(EXAMPLE);
  auto sut = Sensor(in);

  EXPECT_THAT(sut.x, Eq(2));
  EXPECT_THAT(sut.y, Eq(18));
  EXPECT_THAT(sut.r, Eq(7));
}
