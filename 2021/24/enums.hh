#pragma once
#include<string>

enum class Command {inp, add, mul, div, mod, eql};
enum class  Storage {w, x, y, z};

Command command(std::string const&);
