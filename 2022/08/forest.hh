#pragma once
#include <vector>
#include "tree_line.hh"
#include <string>

class Forrest : std::vector<TreeLine>
{
  
public:
  Forrest(std::vector<std::string>const &vs);
  Forrest(std::vector<TreeLine> data);

  using std::vector<TreeLine>::operator[];
  using std::vector<TreeLine>::size;

  Forrest	transpose	() const;
  int		countVisible	() const;
  std::string	toString	() const;
  
  Forrest	sweep		();
  void		sweepLines	();
};
