#include "solution.hh"
#include "row_type.hh"
#include <sstream>
#include <limits>

using namespace std;
Solution & Solution::operator<<(std::string const &row)
{
  switch(rowType(row))
    {
    case RowType::Cd:
      {
	n.cd({next(row.begin(), 5), row.end()});
	t.mkdir(n.path());
	break;
      }
    case RowType::File:
      {
	istringstream in(row);
	size_t val;
	in>>val;
	t.setPath(n.path());
	t.addFile(val);
	break;
      }
    case RowType::Ignore:
      break;
    }
  return *this;
}

long long int Solution::ans() const
{
  long long int ret{0};
  for(auto x: t.allTotalSizes())
    if(x<=100000)
      ret+=x;
  return ret;
}

size_t Solution::requiredSpace() const
{
  return t.totalSize("/") - 40000000;
}

size_t Solution::smallest() const
{
  auto       ret = std::numeric_limits<std::size_t>::max();
  auto const rs  = requiredSpace();
  for(auto a: t.allTotalSizes())
    if ( (a>=rs) and (a < ret) )
      ret = a;
  return ret;
}
