#pragma once
#include <vector>
#include <istream>
#include <string>
#include <fstream>

template<typename T=std::string>
std::vector<T> getAllLines(std::istream &in)
{
  std::vector<T> ret;
  std::string s;
  while(not getline(in, s).eof())
    ret.push_back(s);
  ret.push_back(s);
  return ret;
}

template<typename T=std::string>
std::vector<T> getAllLines()
{
  std::ifstream in(INPUT);
  return getAllLines<T>(in);
}
