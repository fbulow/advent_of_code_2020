#pragma once
#include <vector>
#include <istream>
#include <string>
#include <fstream>
#include <cassert>
#include <set>

void add(std::set<auto> &data, auto element)
{
  data.emplace(move(element));
}
void add(std::vector<auto> &data, auto element)
{
  data.emplace_back(move(element));
}

template<typename T=std::string>
std::vector<T> getAllLines(std::istream &in)
{
  assert(in.good());
  std::vector<T> ret;
  std::string s;
  while(not getline(in, s).eof())
    add(ret, s);
  add(ret, s);

  return ret;
}

template<typename T=std::string>
std::vector<T> getAllLines(std::string const &filename)
{
  std::ifstream in(filename);
  return getAllLines<T>(in);
}

template<typename T=std::string>
std::vector<T> getAllLines()
{
  std::ifstream in(INPUT);
  return getAllLines<T>(in);
}
