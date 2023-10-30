#pragma once
#include "for_each_path.hh"
#include "types.hh"
#include <functional>

Flow SolA(std::function<Flow(Path)> const& totalFlow, ForEachPath);
