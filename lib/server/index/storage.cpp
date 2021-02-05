#include "storage.h"

#include "lib/server/index/ram.h"

namespace search {

void IndexStorage::InitializeStorage(const std::shared_ptr<SearchConfig> & pConfig) {
	m_pConfig = pConfig;

	for (auto& [sName, pIndexConfig] : m_pConfig->index) {
		if (pIndexConfig->iIndexType == IndexType::Template) {
			continue;
		}

		AttachIndex(sName, pIndexConfig);
	}
}

bool IndexStorage::AttachIndex(const std::string& sName, const std::shared_ptr<IndexConfig>& pConfig) {
	auto& pIndex = m_hStorage[sName];

	if (pIndex != nullptr) {
		return false;
	}

	switch (pConfig->iIndexType) {
		case IndexType::Template:
			throw std::runtime_error("Attempt to attach template index");
		case IndexType::Dummy:
			logInfo("Processing index " << pConfig->sIndexName);
			pIndex = std::make_shared<RamSegment>(pConfig);
			break;
		default:
			throw std::runtime_error("Index storage does not support this index type");
	}

	return true;
}

std::shared_ptr<Index> IndexStorage::GetIndex(const std::string &index_name) const {
	auto iterator = m_hStorage.find(index_name);
	if (iterator == m_hStorage.end()) {
		return nullptr;
	}

	return iterator->second;
}

}