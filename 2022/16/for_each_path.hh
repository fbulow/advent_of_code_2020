#pragma once

#include<functional>
#include "path.hh"
using PathCallback = std::function<void(Path const &)>;
using ForEachPath = std::function<void (PathCallback)>;

void allSequenceOfOpenings(PathCallback &);
