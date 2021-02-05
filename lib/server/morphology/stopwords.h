#pragma once

#include "filter.h"
#include <unordered_set>

#include <filesystem>

namespace search {

namespace fs = std::filesystem;

class StopWords : public Filter {
public:
	explicit StopWords(const fs::path & sFileName);

	virtual std::optional<String> Produce() override;
	virtual void Consume(const String &) override;

private:
	// Your code goes here...
};

}