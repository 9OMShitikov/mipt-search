#pragma once

#include <variant>
#include <vector>

using Value = std::variant<uint64_t>;
using Row = std::vector<Value>;
using RowIndex = int;
