#pragma once

#include "index.h"

#include "lib/server/morphology/morph.h"

#include "lib/common/config.h"

#include "lib/std/string.h"

namespace search {

class RamSegment : public Index {
public:
    using IndexData = std::unordered_map<String, std::vector<Hit>>;

    explicit RamSegment(const std::shared_ptr<IndexConfig> & pIndexConfig);

    void ExecuteSelect(const Query &tQuery);

    void Flush(const std::string & sPath);

private:
	std::unordered_map<uint32_t, std::vector<Hit>> GetQueryHits(const Query &tQuery);

	void AddField(const String & sField, uint32_t iDocumentId, uint8_t iFieldId);

private:
	// Your code goes here...

	int m_iUsedRam = 0;

	IndexStats m_sStats;
	IndexMetadata m_dMetadata;
	IndexData m_dDataIndex;
};

}