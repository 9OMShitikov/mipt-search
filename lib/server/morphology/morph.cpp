#include "morph.h"

#include <filesystem>

#include "lower.h"
#include "mappings.h"
#include "stemming.h"
#include "stopwords.h"

namespace search {

namespace fs = std::filesystem;

// init morphology; exact order is important
std::shared_ptr<Filter> CreateFilter(
	const std::shared_ptr<IndexConfig> &pConfig) {
	// this filter should be always
	std::shared_ptr<Filter> tFilter = std::make_shared<Lower>();
	std::shared_ptr<Filter> tLast = tFilter;

	auto fCheck = [](const auto &oPath) {
		if (!oPath) return false;

		if (!fs::exists(*oPath)) {
			logWarning("Morphology file doesn't exist: " << *oPath);
			logWarning("Skipping...");
			return false;
		}

		return true;
	};

	// Your code goes here...
	// Create filter with config

	return tFilter;
}

}  // namespace search