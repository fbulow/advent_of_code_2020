#include "solA.hh"

Flow SolA(std::function<Flow(Path)>  totalFlow, PathGenerator & pathGenerator)
{
  Flow ret{0};
  auto path = pathGenerator.next();
  while(path)
    {
      ret = std::max(ret, totalFlow(path.value()));
      path = pathGenerator.next();
    }
  return ret;
}
