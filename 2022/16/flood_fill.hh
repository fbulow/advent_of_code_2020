#pragma once
#include "input.hh"
#include "valve_connection.hh"
#include <vector>
#include "regions.hh"
#include "path_iteration.hh"

using FromToMinutesCallback = std::function<void(Valve, Valve, Minutes)>;

void floodFillRec(std::function<void(Valve, Minutes)> destAndRemaining,
		  std::function<Valves(Valve const &)> adjacent,
		  Regions const &r,
		  Minutes remaining
		  );

void floodFill(FromToMinutesCallback ret,
	       Input const &data,
	       Valve const &startAt,
	       Minutes const total
	       );
