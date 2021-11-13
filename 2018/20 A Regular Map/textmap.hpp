#pragma once
#include <iostream>
#include <vector>
#include <iostream>
using namespace std;

class Doors;

class Textmap
{
  vector<vector<char>> data;
  void init(istream &in);
public:
  Textmap(string in);
  Textmap(istream &in);
  friend ostream& operator<<(ostream& out, Textmap const &x);
  char operator()(size_t row, size_t column) const;
    void write_to(Doors &d);
};


ostream& operator<<(ostream& out, Textmap const &x);
