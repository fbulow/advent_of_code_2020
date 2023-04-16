#pragma once
#include <vector>
#include <string>
#include <strong_type.hpp>

using namespace std;

struct Valve : strong::type<string, struct Valve_,  strong::regular>
{
  using Parent = strong::type<string, struct Valve_,  strong::regular>;
  Valve(char const * const charArray)
    :Parent(charArray)
  {}
};

inline
bool operator==(Valve const & v, const char* const other)
{return value_of(v)==other;}


using Destinations = vector<Valve>;
using Steps = int;
using Minutes = int;
