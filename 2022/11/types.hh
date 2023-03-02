#pragma once
#include <functional>

using WorryValue = int;
using WorryManager = std::function<WorryValue(WorryValue v)>;
