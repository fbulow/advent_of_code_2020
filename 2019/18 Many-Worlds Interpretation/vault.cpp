#include "vault.hpp"

ostream& operator<<(ostream& out, Vault const &v)
{
  for(auto const &x:v.map)
    out<<x<<endl;
  return out;
}

