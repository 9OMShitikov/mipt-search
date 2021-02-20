#pragma once

class CsvParser {
   public:
	using Result = std::vector<std::wstring>;

   public:
	static Result ParseLine(const std::wstring &sLine) {
		Result tResult;
		uint32_t iPos = 0;
		auto sIdFieldValue = ParseField(sLine, iPos);
		auto sTitleFieldValue = ParseField(sLine, iPos);
		auto sDescFieldValue = ParseField(sLine, iPos);

		return {sIdFieldValue, sTitleFieldValue, sDescFieldValue};
	}

   private:
	static std::wstring ParseField(const std::wstring &sLine, uint32_t &iPos) {
		wchar_t cStopSymbol;
		if (sLine[iPos] == L'"') {
			cStopSymbol = L'"';
			++iPos;
		} else {
			cStopSymbol = L',';
		}
		std::wstring sResult;
		for (uint32_t i = iPos; i < sLine.length(); ++i) {
			if (sLine[i] == cStopSymbol) {
				sResult = sLine.substr(iPos, i - iPos);
				if (cStopSymbol == L'"') {
					iPos = i + 2;
				} else {
					iPos = i + 1;
				}
				return sResult;
			}
		}
		return L"";
	}
};
