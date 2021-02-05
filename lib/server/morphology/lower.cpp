#include "lower.h"

#include "lib/std/string.h"

namespace search {

std::optional<String> Lower::Produce() {
	if (!m_pNext) {
		auto tResult = m_oWord;
		m_oWord = std::nullopt;
		return tResult;
	}

	return m_pNext->Produce();
}

void Lower::Consume(const String &sWord) {
	if (!m_pNext)
		m_oWord = ToLower(sWord);
	else
		m_pNext->Consume(ToLower(sWord));
}

}