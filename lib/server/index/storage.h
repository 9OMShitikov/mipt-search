#pragma once

#include "index.h"
#include "lib/common/config.h"

#include <unordered_map>
#include <memory>

namespace search {

class IndexStorage {
public:
	IndexStorage() = default;

	void InitializeStorage(const std::shared_ptr<SearchConfig>& pConfig);
	bool AttachIndex(const std::string& sName, const std::shared_ptr<IndexConfig>& pConfig);

	std::shared_ptr<Index> GetIndex(const std::string& index_name) const;

private:
	std::shared_ptr<SearchConfig> m_pConfig;
	std::unordered_map<std::string, std::shared_ptr<Index>> m_hStorage;
};

}