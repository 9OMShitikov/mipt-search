#include <filesystem>
#include <iostream>

#include "lib/common/config.h"
#include "lib/server/index/ram.h"
#include "lib/std/logger.h"

using namespace search;

namespace fs = std::filesystem;

void BuildIndex(const fs::path &sDataDir,
				const std::shared_ptr<IndexConfig> &pIndexConfig) {
	// Your code goes here...
}

void PrintHelp() { std::cout << "usage: indexer [config path]\n"; }

int main(int argc, char **argv) {
	if (argc != 2) {
		PrintHelp();
		return 1;
	}

	std::shared_ptr<SearchConfig> pConfig = nullptr;
	try {
		pConfig = LoadConfig(argv[1]);
	} catch (std::runtime_error &error) {
		logFatal("Config file '" << argv[1] << "': " << error.what());
	}

	int iSuccess = 0, iFailed = 0;
	for (auto &[sIndexName, pIndexConfig] : pConfig->index) {
		if (pIndexConfig->iIndexType != IndexType::Plain) {
			logWarning("Skipping non-plain index '" << sIndexName << "'...");
			continue;
		}

		try {
			BuildIndex(pConfig->indexDirectory, pIndexConfig);
			++iSuccess;
		} catch (std::runtime_error &error) {
			++iFailed;
			logWarning("Can't build plain index: " << error.what());
		}
	}

	return ((iSuccess > 0) && (iFailed == 0));
}