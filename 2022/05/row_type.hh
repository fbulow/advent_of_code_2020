#pragma once
#include <string>

enum class RowType{ Setup, Move, Ignore };

RowType rowType(std::string const & s);

