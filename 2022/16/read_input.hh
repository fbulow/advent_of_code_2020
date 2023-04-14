#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> readInput(istream &in);

inline
auto readInput(string const &filename)
{
  ifstream in(filename);
  return readInput(in);
}




  
