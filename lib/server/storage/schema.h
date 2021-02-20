#include <variant>
#include <vector>

enum class ColumnType { Int, Double, Uint32, Wstring };

using Column = std::variant<int, double, uint32_t, std::wstring>;

using Row = std::vector<Column>;

struct Schema {
	std::vector<std::pair<std::string, ColumnType>> columns;
};
