#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<fstream>
#include<sstream>
#include<ranges>

#include<structured_input.hh>

using namespace std;

using Coord = pair<int,int>;

struct Claim
{
  int id, x, y, width, height;
};

istream& operator>>(istream& in, Claim &c)
{
  in>>"#">>c.id>>" @ ">>c.x>>",">>c.y>>": ">>c.width>>"x">>c.height;
  return in;
}

vector<pair<int, int>> coord(istream &in)
{
  int id, x, y, width, height;

  //"#1 @ 1,3: 2x2"

  vector<pair<int, int>> ret;
  for(int i=0;i<height;i++)
    for(int j=0;j<width;j++)
      ret.emplace_back(x+j, y+i);
  return ret;
}

vector<Coord> const coords(Claim c)
{
  vector<Coord> ret;
  ret.clear();
  for(int i=0;i<c.height;i++)
    for(int j=0;j<c.width;j++)
      ret.emplace_back(c.x+j, c.y+i);

  return ret;
}
vector<Coord> coords(string const &s)
{
  istringstream in(s);
  Claim c;
  in>>c;
  return coords(c);
}

//int solB(

using namespace testing;
TEST(a, coords)
{
  EXPECT_THAT(coords("#1 @ 1,3: 2x2").size(), Eq(4));
  EXPECT_THAT(coords("#1 @ 1,3: 2x3").size(), Eq(6));
  EXPECT_THAT(coords("#1 @ 1,3: 2x3"), Contains(Coord(1,3)));
  EXPECT_THAT(coords("#1 @ 1,3: 2x2"), Contains(Coord(2,4)));
  EXPECT_THAT(coords("#1 @ 1,3: 1x2"), Not(Contains(Coord(2,4))));
}

istream& operator>>(istream& in, vector<Claim>&v)
{
  Claim claim;
  in>>claim;
  try
    {
      while(true)
	{
	  v.push_back(claim);
	  in>>claim;
	}
    }
  catch(...){}
  return in;
}

set<Coord> overlaps(vector<Claim> const &claims)
{
  map<Coord, int> count;
  for(auto const &cl: claims)
    for(Coord const & co: coords(cl))
      count[co]++;

    set<Coord> ret;
    
    for (auto const & x :
	   count
	   |views::filter([](auto const &x){return x.second>1;}))
      ret.insert(x.first);
    return ret;
}

vector<Claim> const & input()
{
  static vector<Claim> ret;
  if(ret.empty())
    {
      ifstream in(INPUT);
      in>> ret;
      assert(not ret.empty());
    }
  return ret;
}

int solA(vector<Claim> const &input)
{
  return overlaps(input).size();
};


int solB(vector<Claim> const &input)
{
  auto o = overlaps(input);
  for(auto &c: input)
    {
      auto co = coords(c);
      if(none_of(co.begin(),
		 co.end(),
		 [o](Coord c)
		 {
		   return o.contains(c);
		 }))
	return c.id;
    }
  assert(false);
};




TEST(a, example)
{
  istringstream in("#1 @ 1,3: 4x4\n"
		   "#2 @ 3,1: 4x4\n"
		   "#3 @ 5,5: 2x2\n");
  vector<Claim> data;
  in>>data;
  EXPECT_THAT(solA(data), Eq(4));
	
}

TEST(formated_read, second_char_is_diff)
{
  istringstream in("ost");
  try
    {
    in>>"oSt";
    }
  catch(Missmatch &m)
    {
      EXPECT_THAT(m.expected(), Eq("oS"));
      EXPECT_THAT(m.got(),      Eq("os"));
    }
}

TEST(a, solution)
{
  EXPECT_THAT(solA(input()), Eq(101196));
}


TEST(b, example)
{
  istringstream in("#1 @ 1,3: 4x4\n"
		   "#2 @ 3,1: 4x4\n"
		   "#3 @ 5,5: 2x2\n");

  vector<Claim> d(3);

  in>>d[0];
  in>>d[1];
  in>>d[2];
  
  EXPECT_THAT(solB(d), Eq(3));
  
}

TEST(b, solution)
{
  EXPECT_THAT(solB(input()), Eq(243));
}
