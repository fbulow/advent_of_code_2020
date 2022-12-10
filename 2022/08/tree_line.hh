#pragma once
#include <vector>
#include <string_view>
#include <ostream>

#include "tree.hh"

struct TreeLine:std::vector<Tree>
{
  TreeLine(){}
  TreeLine(std::string_view s)
    :vector<Tree>(s.begin(), s.end())
  {}
  using std::vector<Tree>::resize;
  using std::vector<Tree>::operator[];
  using std::vector<Tree>::begin;
  using std::vector<Tree>::end;

  int countVisible() const;
};

std::ostream& operator<<(std::ostream& out, TreeLine const & tl);
