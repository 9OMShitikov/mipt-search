#pragma once

#include "index.h"
#include "lib/common/config.h"
#include "lib/server/morphology/morph.h"
#include "lib/std/string.h"

namespace search
{
class RamSegment : public Index
{
public:
	using IndexData = std::unordered_map<String, std::vector<Hit>>;

	RamSegment() = default;
	explicit RamSegment(const std::shared_ptr<IndexConfig> & pIndexConfig);

	virtual void ExecuteSelect(const Query & tQuery);

	void Flush(const std::string & sPath);

	inline void SetData(const IndexData & data) { m_dDataIndex = data; };
	inline IndexData GetData() const { return m_dDataIndex; };

private:
	std::unordered_map<uint32_t, std::vector<Hit>> GetQueryHits(
		const Query & tQuery);

	void AddField(const String & sField, uint32_t iDocumentId, uint8_t iFieldId);

private:
	// Your code goes here...

	int m_iUsedRam = 0;

	IndexStats m_sStats;
	IndexMetadata m_dMetadata;
	IndexData m_dDataIndex;
};

} // namespace search