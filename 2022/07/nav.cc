#include "nav.hh"

void Nav::cd(std::string const &s)
{
  if(s=="/")
    pwd=s;
  else if (s=="..")
    pwd.resize(std::max(size_t(pwd.rfind('/')), size_t(1)));
  else if (pwd=="/")
    pwd+=s;
  else
    pwd+=std::string("/")+=s;
}

std::string const & Nav::path() const
{
  return pwd;
}
