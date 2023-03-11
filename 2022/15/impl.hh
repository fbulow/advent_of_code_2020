#pragma once
#include <fstream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include<array>

using namespace std;

using Int = int;


Int getInt(istream &in);
struct Sensor{
  Int x;
  Int y;
  Int bx;
  Int by;

  Int r;

  Sensor(istream &in)
    :x(getInt(in))
    ,y(getInt(in))
    ,bx(getInt(in))
    ,by(getInt(in))
    ,r(abs(x-bx) + abs(y-by))
  {
    assert(r>=0);
    if(in.eof())
      throw exception();
  }
};


vector<Sensor> getData(string filename);

Int countOn(Int const activeSensors,
	    Int const startIndex,
	    auto const begin,
	    auto const end);


Int countOn(map<Int, int> const &onOff);

Int beaconsOnRow(vector<Sensor> const &sensors, Int row);

Int crapOnRow(vector<Sensor> const &sensors, Int row);

Int watchedLocationsCount(vector<Sensor> const &sensors, Int row);

Int solutionA(string filename, Int row);
