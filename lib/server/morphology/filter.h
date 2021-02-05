#pragma once

#include "lib/std/string.h"

#include <optional>

namespace search {

struct Filter {
	virtual std::optional<String> Produce() = 0;
	virtual void Consume(const String & sWord) = 0;

	inline void Attach(const std::shared_ptr<Filter> & pFilter) {
		m_pNext = pFilter;
	}

	std::shared_ptr<Filter> m_pNext = nullptr;
};

}