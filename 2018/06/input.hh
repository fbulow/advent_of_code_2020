#pragma once
#include <tuple>
#include <vector>

using namespace std;
using Coord = pair<int, int>;
using Data = vector<Coord>;

namespace Input{
  Data example();
};

void normalize(Data &);


#include<cassert>
#include<algorithm>

int minRow(Data const &d);
int minCol(Data const &d);
int maxRow(Data const &d);
int maxCol(Data const &d);

