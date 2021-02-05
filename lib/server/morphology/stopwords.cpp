#include "stopwords.h"

#include <fstream>
#include <iostream>

namespace search {

StopWords::StopWords(const fs::path & sFileName) {
	// Your code goes here...
}

std::optional<String> StopWords::Produce() {
	// Your code goes here...

	return std::nullopt;
}

void StopWords::Consume(const String & sWord) {
	// Your code goes here...
}

}