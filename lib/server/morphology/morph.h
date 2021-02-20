#pragma once

#include <memory>

#include "filter.h"
#include "lib/common/config.h"

namespace search
{
std::shared_ptr<Filter> CreateFilter(
	const std::shared_ptr<IndexConfig> & pConfig);
// Your code goes here...
} // namespace search