#include "row_type.hh"
#include <predicate.hpp>
using boost::algorithm::starts_with;
RowType rowType(std::string const &s)
{
  if(starts_with(s, "$ cd "))
    return RowType::Cd;
  else if (s == "$ ls")
    return RowType::Ignore;
  else if (starts_with(s, "dir "))
    return RowType::Ignore;
  else
    return RowType::File;
}
