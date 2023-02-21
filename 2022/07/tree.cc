#include "tree.hh"

#include <predicate.hpp>

void Tree::addFile(size_t s)
{data[pwd]+=s;}

std::size_t Tree::size()
{return data[pwd];}
  
std::size_t Tree::totalSize(std::string const & path) const
{
  size_t ret{0};
  for(auto const & p : data)
    if(boost::algorithm::starts_with(p.first, path))
      ret+=p.second;
  return ret;
}
  
void Tree::setPath(std::string dir)
{
  pwd = dir;
}
  
  

    
  

