#pragma once

#include <memory>
#include <string>

#include "filter.h"
#include "stemming_impl.h"

namespace search
{
class Stemmer : public Filter
{
public:
	explicit Stemmer(const std::string & path);

	virtual std::optional<String> Produce() override;
	virtual void Consume(const String &) override;

	// TODO: in private
	std::string Process(const std::string & string);

private:
	std::optional<String> m_sWord;
	std::shared_ptr<StemmingImpl> impl_;
};

} // namespace search