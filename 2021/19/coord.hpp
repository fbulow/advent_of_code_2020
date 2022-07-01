#pragma once

struct Coord{
  int x;
  int y;
  int z;
};

using Beacons = vector<Coord>;

Coord operator-(Coord const &a, Coord const &b)
{
  return {a.x-b.x, a.y-b.y, a.z-b.z};
}

bool operator!=(Coord const &a, Coord const &b)
{
  return (a.x!=b.x)
    or (a.y!=b.y)
    or (a.z!=b.z);
}
bool operator<(Coord const &a, Coord const &b)
{
  if(a.x==b.x)
    if(a.y==b.y)
      if(a.z==b.z)
        return false;
      else
        return a.z<b.z;
    else
      return a.y<b.y;
  else
    return a.x<b.x;
}

bool operator==(Coord const &a, Coord const &b)
{
  return (a.x==b.x) and (a.y==b.y) and (a.z==b.z);
}
int maxAbs(Coord const &c)
{
  array<int, 3> x{abs(c.x), abs(c.y), abs(c.z)};
  return *max_element(x.begin(), x.end());
}

TEST(maxAbs, val)
{
  EXPECT_EQ(10, maxAbs({1, 5, -10}));
  EXPECT_EQ(5, maxAbs({1, 5, 2}));
}

bool inScannerRange(Coord const & scanner, Coord const & beacon)
{
  return maxAbs(beacon-scanner)<=1000;
}

TEST(inScannerRange, example)
{
  EXPECT_TRUE( inScannerRange( {0,0,0}, {-1000, 1000, 50}) );
  EXPECT_FALSE( inScannerRange( {0,0,0}, {-1001, 1000, 50}) );
  EXPECT_FALSE( inScannerRange( {1,0,0}, {-1001, 1000, 50}) );
  EXPECT_TRUE( inScannerRange( {-1,0,0}, {-1001, 1000, 50}) );
  EXPECT_TRUE( inScannerRange( {1,0,0}, {-40, 11, 52}) );
}  

Coord cross(Coord const& a, Coord const& b)
{
  return {
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x*b.z,
    a.x*b.y - a.y*b.x
  };
}

function<Coord(Coord const&)> transformation(Coord x, Coord y)
{
  Coord z = cross(x,y);
  return [x,y,z](Coord const& v)
  {
    return Coord{
      v.x*x.x + v.y*y.x + v.z*z.x,
      v.x*x.y + v.y*y.y + v.z*z.y,
      v.x*x.z + v.y*y.z + v.z*z.z
    };
      
  };
}

TEST(transformation, axis)
{
  EXPECT_EQ( 2, transformation({1,0,0},{0,1,0})({0,0,2}).z);
  EXPECT_EQ( 0, transformation({1,0,0},{0,1,0})({0,0,2}).x);
  EXPECT_EQ( 0, transformation({1,0,0},{0,1,0})({0,0,2}).y);
  EXPECT_EQ( 3, transformation({1,0,0},{0,1,0})({0,3,2}).y);
  EXPECT_EQ(-2, transformation({0,1,0},{1,0,0})({0,0,2}).z);
  EXPECT_EQ(-2, transformation({-1,0,0},{0,1,0})({2,3,4}).x);
}

Coord operator-(Coord const &c)
{
  return {-c.x, -c.y, -c.z};
}

vector<function<Coord(Coord const& c)>> const & orientations()
{
  static auto ret = [] // evaluated immediately
  {
    vector<function<Coord(Coord const& c)>> ret;
    ret.reserve(24);
    vector<Coord> axis{{ 1, 0, 0},
                       { 0, 1, 0},
                       { 0, 0, 1},
                       {-1, 0, 0},
                       { 0,-1, 0},
                       { 0, 0,-1}};
  
    for(auto x : axis)
      for(auto y : axis)
        if( (x!=y) and (x!=-y) )
          ret.emplace_back(transformation(x,y));
    return ret;
  }();
  return ret;
}
TEST(orientations, some)
{
  EXPECT_EQ(24,
            orientations().size());
}


function<Coord(Coord)> translateFromTo(Coord const &a, Coord const &b)
{
  auto dx = b.x-a.x;
  auto dy = b.y-a.y;
  auto dz = b.z-a.z;
  return [dx, dy, dz](Coord const & p) ->Coord
  {
    return {p.x+dx, p.y+dy, p.z+dz};
  };
}


TEST(translateFromTo, some)
{
  auto sut = translateFromTo({1,2,3}, {4,51,63})({1,2,3});
  
  EXPECT_EQ( 4,  sut.x );
  EXPECT_EQ( 51, sut.y );
  EXPECT_EQ( 63, sut.z );
}

