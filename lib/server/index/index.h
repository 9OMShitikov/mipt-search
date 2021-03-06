#pragma once

#include <codecvt>
#include <fstream>
#include <locale>
#include <string>

#include "lib/common/types.h"
#include "lib/server/engine/ranking.h"
#include "lib/server/morphology/filter.h"
#include "lib/std/logger.h"

namespace search
{
class Index
{
public:
	virtual void ExecuteSelect(const Query & tQuery) = 0;

	inline std::shared_ptr<Filter> GetMorph() const { return m_pFilter; }

protected:
	std::shared_ptr<Filter> m_pFilter = nullptr;
};

class IPostingIterator
{
public:
	virtual Hit * operator->() = 0;

	virtual IPostingIterator & operator++() = 0;

	virtual bool Empty() = 0;
};

} // namespace search