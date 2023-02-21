#include "sol_a.hh"
#include "row_type.hh"
#include <sstream>
using namespace std;
SolA & SolA::operator<<(std::string const &row)
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

long long int SolA::ans() const
{
  long long int ret{0};
  for(auto x: t.allTotalSizes())
    if(x<=100000)
      ret+=x;
  return ret;
}

