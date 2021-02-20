#pragma once

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <unordered_map>

#include "lib/std/logger.h"
#include "types.h"

struct IndexConfig {
	std::string sIndexName;
	IndexType iIndexType;
	std::string sSource;
	std::string sIndexDataPath;
	std::optional<std::string> sPathToStemmer = std::nullopt;
	std::shared_ptr<IndexConfig> pInherit = nullptr;
	std::optional<std::string> sStopwords = std::nullopt;
	std::optional<std::string> sWordForms = std::nullopt;

	explicit IndexConfig(std::string sIndexName = "",
						 IndexType iIndexType = IndexType::Template,
						 std::string sSource = "",
						 std::string sIndexDataPath = "",
						 std::string sPathToStemmer = "",
						 std::shared_ptr<IndexConfig> pInherit = nullptr,
						 std::string sStopwords = "",
						 std::string sWordForms = "")
		: sIndexName(std::move(sIndexName))
		, iIndexType(iIndexType)
		, sSource(std::move(sSource))
		, sIndexDataPath(std::move(sIndexDataPath)) {
		if (!sPathToStemmer.empty()) {
			this->sPathToStemmer = std::move(sPathToStemmer);
		}
		if (pInherit) {
			this->pInherit = std::move(pInherit);
		}
		if (!sStopwords.empty()) {
			this->sStopwords = std::move(sStopwords);
		}
		if (!sWordForms.empty()) {
			this->sWordForms = std::move(sWordForms);
		}
	}

	static std::shared_ptr<IndexConfig> DummyIndexConfig(
		std::string sSource = "",
		std::string sIndexDataPath = "",
		std::string sPathToStemmer = "",
		std::shared_ptr<IndexConfig> pInherit = nullptr,
		std::string sStopwords = "",
		std::string sWordForms = "") {
		return std::make_shared<IndexConfig>("dummy",
											 IndexType::Dummy,
											 std::move(sSource),
											 std::move(sIndexDataPath),
											 std::move(sPathToStemmer),
											 std::move(pInherit),
											 std::move(sStopwords),
											 std::move(sWordForms));
	}
};

struct SearchConfig {
	std::unordered_map<std::string, std::shared_ptr<IndexConfig>> index;
	std::string indexDirectory;
};

inline std::shared_ptr<SearchConfig> LoadConfig(const std::string &path) {
	std::ifstream in(path);

	if (!in.is_open()) throw std::runtime_error(strerror(errno));

	auto searchConfig = std::make_shared<SearchConfig>();

	std::string token;
	while (in >> token) {
		if (token == "index") {
			std::string index_name;
			in >> index_name;
			auto &indexConfig = searchConfig->index[index_name];
			indexConfig = std::make_shared<IndexConfig>();

			indexConfig->sIndexName = index_name;

			in >> token;
			if (token == ":") {
				// it means that index inherits from
				in >> token;

				if (searchConfig->index.find(token) !=
					searchConfig->index.end())
					indexConfig->pInherit = searchConfig->index[token];
				else {
					logWarning("No inherit index" << token << " for "
												  << index_name);
					logWarning("Skipping...");
				}

				in >> token;
			}

			assert(token == "{");

			// start option section
			while (in >> token && token != "}") {
				std::string sep, value;
				in >> sep >> value;
				assert(sep == "=");

				if (token == "type") {
					indexConfig->iIndexType = GetIndexTypeFromName(value);
				} else if (token == "stopwords") {
					indexConfig->sStopwords = value;
				} else if (token == "wordforms") {
					indexConfig->sWordForms = value;
				} else if (token == "path") {
					indexConfig->sSource = {value};
				} else if (token == "stemmer") {
					indexConfig->sPathToStemmer = value;
				} else
					assert(0);
			}
		} else if (token == "search") {
			in >> token;
			assert(token == "{");

			// start option section
			while (in >> token && token != "}") {
				std::string sep, value;
				in >> sep >> value;
				assert(sep == "=");

				if (token == "data")
					searchConfig->indexDirectory = value;
				else
					assert(0);
			}
		} else
			assert(0);

		assert(token == "}");
	}

	return searchConfig;
}
