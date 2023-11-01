#pragma once

#include "types.hh"
#include <map>
#include "path.hh"
#include <functional>

using FlowRates = std::function<Flow(Valve const&)>;

Flow totalVolume(Path const & p, FlowRates const & flowRates, Minutes remaining = 30);
