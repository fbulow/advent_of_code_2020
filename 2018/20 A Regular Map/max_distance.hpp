#pragma once
#include "doors.hpp"
#include "strong_type.hpp"

using Distance = strong::type<unsigned int, struct _CurrentPos, strong::regular, strong::arithmetic>;
Distance max_distance(Doors const &d);

