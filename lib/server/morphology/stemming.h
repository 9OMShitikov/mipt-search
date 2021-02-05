#pragma once

#include <string>
#include <memory>

#include "stemming_impl.h"
#include "filter.h"

namespace search {

class Stemmer : public Filter {
public:
	explicit Stemmer(const std::string& path);

	virtual std::optional<String> Produce() override;
	virtual void Consume(const String &) override;

	// TODO: in private
	std::string Process(const std::string& string);

private:
	std::optional<String> m_sWord;
	std::shared_ptr<StemmingImpl> impl_;
};

}