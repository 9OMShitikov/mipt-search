#include "ram.h"

#include <lib/common/types.h>
#include <sys/stat.h>

#include <codecvt>
#include <regex>
#include <set>
#include <sstream>
#include <unordered_map>

#include "lib/server/engine/ranking.h"
#include "lib/server/net/context.h"
#include "lib/std/csv_parser.h"
#include "lib/std/string.h"

namespace search {

RamSegment::RamSegment(const std::shared_ptr<IndexConfig> &pIndexConfig) {
	// Init morphology
	m_pFilter = CreateFilter(pIndexConfig);

	uifstream iIn(pIndexConfig->sSource);

	// Building ram index
	if (iIn.is_open()) {
		logInfo("Build RAM index from file " << pIndexConfig->sSource);

		// Your code goes here...
		// help: use CsvParser, AddField

		logInfo("Index ready");
	} else {
		logFatal("Can't open source " << pIndexConfig->sSource);
	}
}

void RamSegment::ExecuteSelect(const Query &tQuery) {
	// Your code goes here...
	// help: create ranker, proceed hits
	// You are able to compute hits and then proceed them
	// Sort result
	// Use tQuery.m_pContext to save your results
}

std::unordered_map<uint32_t, std::vector<Hit>> RamSegment::GetQueryHits(
	const Query &tQuery) {
	static auto fInMask = [](uint32_t iMask, uint8_t iPos) {
		return iMask & (1u << iPos);
	};

	// Your code goes here...
	// help: think about ranking fields
	// you are able to use set and set_intersection

	std::unordered_map<uint32_t, std::vector<Hit>> dWordMatch;
	return dWordMatch;
}

void RamSegment::AddField(const String &sField,
						  uint32_t iDocumentId,
						  uint8_t iFieldId) {
	// Your code goes here...
	// help: use m_pFilter and ParseWords
}

void RamSegment::Flush(const std::string &sPath) {
	// Your code goes here...
}

}  // namespace search