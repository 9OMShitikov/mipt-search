#pragma once

#include <codecvt>
#include <fstream>
#include <locale>
#include <regex>
#include <string>
#include <vector>

namespace search {

using String = std::wstring;

class uifstream : public std::wifstream {
   public:
	uifstream() : std::wifstream() { locale_init(); }
	explicit uifstream(const char *filename,
					   std::ios_base::openmode mode = std::ios_base::in)
		: std::wifstream(filename, mode) {
		locale_init();
	}
	explicit uifstream(const std::string &filename,
					   std::ios_base::openmode mode = std::ios_base::in)
		: std::wifstream(filename, mode) {
		locale_init();
	}
	uifstream(uifstream &&x) noexcept : std::wifstream(std::move(x)) {
		locale_init();
	}

   private:
	void locale_init() {
		this->imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
	}
};

class uofstream : public std::wofstream {
   public:
	uofstream() : std::wofstream() { locale_init(); }

	explicit uofstream(const char *filename,
					   std::ios_base::openmode mode = std::ios_base::in)
		: std::wofstream(filename, mode) {
		locale_init();
	}
	explicit uofstream(const std::string &filename,
					   std::ios_base::openmode mode = std::ios_base::in)
		: std::wofstream(filename, mode) {
		locale_init();
	}
	uofstream(uofstream &&x) noexcept : std::wofstream(std::move(x)) {
		locale_init();
	}

   private:
	void locale_init() {
		this->imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
	}
};

inline std::string ToString(String &&sWord) {
	using convert_type = std::codecvt_utf8<wchar_t>;
	static std::wstring_convert<convert_type, wchar_t> tConverter;
	return tConverter.to_bytes(sWord);
}

inline std::string ToString(const String &sWord) {
	return ToString(String(sWord));
}

inline String ToWstring(std::string &&sWord) {
	using convert_type = std::codecvt_utf8<wchar_t>;
	static std::wstring_convert<convert_type, wchar_t> tConverter;
	return tConverter.from_bytes(sWord);
}

inline String ToWstring(const std::string &sWord) {
	return ToWstring(std::string(sWord));
}

inline String ToLower(String &&sWord) {
	static const std::locale tLocale("");
	for (wchar_t &c : sWord) {
		c = std::tolower(c, tLocale);
	}
	return std::move(sWord);
}

inline String ToLower(const String &sWord) { return ToLower(String(sWord)); }

inline std::vector<String> ParseWords(const String &sField) {
	uint32_t iBeginPos = 0;
	uint32_t iCurrentPos = 0;

	std::vector<String> dWords;

	// TODO: fix
	std::wregex wordRegex(LR"([a-zA-Zа-яА-Я]+)", std::regex::collate);
	while (iCurrentPos < sField.length()) {
		if (sField[iCurrentPos] == L' ') {
			auto sCurrentWord =
				sField.substr(iBeginPos, iCurrentPos - iBeginPos);
			std::wsmatch regexMatch;
			std::regex_search(sCurrentWord, regexMatch, wordRegex);
			iBeginPos = iCurrentPos + 1;
			for (uint32_t i = 0; i < regexMatch.size(); ++i) {
				dWords.push_back(regexMatch.str(i));
				// auto word =
				// ToLower(ToWstring(stemmer.Process(ToString(regexMatch.str(i)))));
			}
		}
		iCurrentPos++;
	}

	return dWords;
}

}  // namespace search