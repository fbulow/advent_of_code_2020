#include<vector>
#include<iostream>
using namespace std;

using Int = int;
using Load = Int;


Load solA(istream &in)
{
  Board b;
  in>>b;
  return b.slideNorth().getLoad();
}



