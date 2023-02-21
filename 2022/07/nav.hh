#pragma once
#include <string>

class Nav{
  std::string pwd{""};
public:
  void cd(std::string const &s);
  std::string const & path() const;
};
