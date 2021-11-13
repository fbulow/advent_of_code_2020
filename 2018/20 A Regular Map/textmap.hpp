#pragma once
#include <iostream>
#include <vector>
#include <iostream>

using namespace std;


class Textmap
{
  vector<vector<char>> data;
  void init(istream &in);
public:
  Textmap(string in);
  Textmap(istream &in);
  friend ostream& operator<<(ostream& out, Textmap const &x);
};


ostream& operator<<(ostream& out, Textmap const &x);
