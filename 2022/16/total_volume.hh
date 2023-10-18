#pragma once

#include "types.hh"
#include <map>
#include "path.hh"

using FlowRates = std::map<Valve, Flow>;

Flow totalVolume(Path const & p, FlowRates const & flowRates, Minutes remaining = 30);
