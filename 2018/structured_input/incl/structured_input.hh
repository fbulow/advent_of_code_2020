#pragma once

#include<istream>
#include<string>
#include<sstream>

std::istream& operator>>(std::istream& in, const std::string &s);

using namespace std;

class Missmatch: public exception{
public:
  string expected_{};
  string got_{};
  mutable string message;

  string expected() const
  {
    return {expected_.rbegin(), expected_.rend()};
  };
  string got() const
  {
    return {got_.rbegin(), got_.rend()};
  };

  Missmatch(char cexpected,
	   char cgot)
  {
    expected_+=cexpected;
    got_+=cgot;
  }
  Missmatch(string expected,
	   string got)
    :expected_(expected)
    ,got_(got)
  {}
  
  const char * what() const noexcept
  {
    ostringstream out;

    string rgot(got_.rbegin(), got_.rend());
    
    out <<endl
	<< "Expected: " << expected()<<endl
	<< "Got:      " << got()<<endl;
    message = out.str();
    
    return message.data();
  }

};
