#include "stemming.h"

namespace search
{
Stemmer::Stemmer(const std::string & path)
	: impl_(std::make_shared<StemmingImpl>(path))
{}

std::optional<String> Stemmer::Produce()
{
	if (!m_pNext)
	{
		auto tResult = m_sWord;
		m_sWord = std::nullopt;
		return tResult;
	}

	return m_pNext->Produce();
}

void Stemmer::Consume(const String & sWord)
{
	auto sComplete = ToWstring(Process(ToString(sWord)));
	if (!m_pNext)
		m_sWord = sComplete;
	else
		m_pNext->Consume(sComplete);
}

std::string Stemmer::Process(const std::string & word)
{
	return impl_->Process(word);
}

} // namespace search