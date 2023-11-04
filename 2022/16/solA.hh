#pragma once
#include "for_each_path.hh"
#include "input.hh"
#include "types.hh"
#include <functional>

Flow SolA(Input const & inp);
Flow SolA(std::function<Flow(Path)> const& totalFlow, ForEachPath);
