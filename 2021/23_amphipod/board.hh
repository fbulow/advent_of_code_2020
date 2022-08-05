#pragma once
#include<array>
#include<string_view>
#include<iostream>
#include<map>

using namespace std;

class Board{
  string s{
    "#############\n"
      "#01 2 3 4 56#\n"
      "###7#8#9#a###\n"
      "  #b#c#d#e#  \n"
      "  #########  \n"};
  map<char, size_t> toIndex;
public:
  Board();
  long score{0};
  void set(char coord, char pod);
  void swap(char a, char b);
  void swap(string_view);
  int incr(size_t ia, size_t ib) const;
  
private:
  friend ostream& operator<<(ostream& cout, Board const& b);
};

ostream& operator<<(ostream& cout, Board const& b);
  
