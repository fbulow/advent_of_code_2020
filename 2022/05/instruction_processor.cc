#include "instruction_processor.hh"
#include <sstream>
#include "stack.hh"
#include <algorithm>
#include "row_type.hh"

using namespace std;

InstructionProcessor& InstructionProcessor::applyRow(std::string const &s)
{
  switch(rowType(s))
    {
    case RowType::Setup:
      {
	size_t stack = 0;
	size_t pos = 1;
    
	while(pos<s.size())
	  {
	    if(stack == data.size())
	      data.emplace_back(Stack());
	    if(s[pos]!=' ')
	      data[stack].push_bottom(s[pos]);
	    pos+=4;
	    stack++;
	  }
	break;
      }
    case RowType::Move:
      {
	istringstream in(s);
	int count;
	size_t from;
	size_t to;
	string word;
	in>>word>>count>>word>>from>>word>>to;
	--from;
	--to;
	while((count--)>0)
	  data[to].push_top(data[from].pop());
	break;
      }
    case RowType::Ignore:
      break;
    }
  return *this;
}


std::string InstructionProcessor::message() const
{
  std::string ret;
  ret.reserve(data.size());
  std::transform(data.begin(),
		 data.end(),
		 std::back_inserter(ret),
		 [](Stack const & s)
		 {return s.top();});
  return ret;
}
