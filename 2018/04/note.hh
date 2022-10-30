#pragma once
#include<string>
#include<set>
#include"time.hh"
using namespace std;

enum class Action  {sleep, wake, guard};

class Note{
  Note(string const &s);
public:
  Note(auto const&x)
  :Note(string(x))
  {}
  Note() = default;
  Time t;
  Action a;
  int guard;
};

istream& operator>>(istream& in, Note&n);
bool operator<(Note const &a, Note const &b);
