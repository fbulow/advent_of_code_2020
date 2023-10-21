#pragma once
#include "path_generator.hh"
#include "types.hh"
#include <functional>

Flow SolA(std::function<Flow(Path)> const& totalFlow, PathGenerator & pathGenerator);
