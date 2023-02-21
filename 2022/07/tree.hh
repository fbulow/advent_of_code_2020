#pragma once
#include <map>
#include <string>
#include <vector>

class Tree{
  std::map<std::string, std::size_t> data;
  std::string pwd{"/"};
  size_t total{0};
public:
  void addFile(std::size_t s);
  void setPath(std::string dir);
  std::size_t size();
  std::size_t totalSize(std::string const & path) const;

};
