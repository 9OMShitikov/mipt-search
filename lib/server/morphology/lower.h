#pragma once

#include "filter.h"

namespace search {

class Lower : public Filter {
   public:
	std::optional<String> Produce() override;

	void Consume(const String &sWord) override;

   private:
	std::optional<String> m_oWord;
};

}  // namespace search