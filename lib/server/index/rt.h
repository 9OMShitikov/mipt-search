#pragma once

#include <memory>

#include "disk.h"
#include "index.h"
#include "ram.h"

namespace search
{
class RTIndex : public Index
{
	virtual void ExecuteSelect(const Query & tQuery);

private:
	std::unique_ptr<RamSegment> pRamSegment;
	std::vector<std::unique_ptr<DiskSegment>> m_dDiskSegments;
};

} // namespace search