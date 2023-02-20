#include "row_type.hh"

RowType rowType(std::string const & s)
{
  if (s.empty())
    return RowType::Ignore;
  else if(s[0]==' ' and s[1] == '1')
    return RowType::Ignore;
  else if(s[0]=='m')
    return RowType::Move;
  else
    return RowType::Setup;
}
