#pragma once

#include "index.h"

#include "ram.h"
#include "disk.h"

#include <memory>

namespace search {

class RTIndex : public Index
{
	virtual void ExecuteSelect(const Query &tQuery);


private:
	std::unique_ptr<RamSegment> pRamSegment;
	std::vector<std::unique_ptr<DiskSegment>> m_dDiskSegments;
};

}