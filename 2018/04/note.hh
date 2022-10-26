#pragma once
#include<string>
#include<set>
#include"time.hh"
using namespace std;

enum class Action  {sleep, wake, guard};

class Note{
public:
  Note(string const &s);
  Note() = default;
  Time t;
  Action a;
  int guard;
};

istream& operator>>(istream& in, Note&n);
bool operator<(Note const &a, Note const &b);
