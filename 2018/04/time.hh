#pragma once
#include<istream>
#include<structured_input.hh>
using namespace std;

class Time{
public:
  int year;
  int month;
  int day;
  int hour;
  int minute;

  Time(){}
  Time(int year, int month, int day, int hour, int minute)
    :year  (year)  
    ,month (month) 
    ,day   (day)   
    ,hour  (hour)  
    ,minute(minute)
  {}

  Time(string const &s);
};

bool operator<(Time const &a, Time const &b);
bool operator==(Time const &a, Time const &b);

inline
istream& operator>>(istream& in, Time &t)
{
  in>>"[">>t.year>>"-">>t.month>>"-">>t.day>>" ">>t.hour>>":">>t.minute>>"]";
  return in;
}

inline
ostream& operator<<(ostream& out, Time const &t)
{
    out<<"["<<t.year<<"-"<<t.month<<"-"<<t.day<<" "<<t.hour<<":"<<t.minute<<"]";
  return out;
}  
