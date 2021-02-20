#pragma once

#include <filesystem>
#include <unordered_set>

#include "filter.h"

namespace search
{
namespace fs = std::filesystem;

class StopWords : public Filter
{
public:
	explicit StopWords(const fs::path & sFileName);

	virtual std::optional<String> Produce() override;
	virtual void Consume(const String &) override;

private:
	// Your code goes here...
};

} // namespace search