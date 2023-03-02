#pragma once
#include <functional>

using WorryValue = long long int;
using WorryManager = std::function<WorryValue(WorryValue v)>;
