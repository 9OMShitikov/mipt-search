#pragma once

#include "lib/std/string.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <cassert>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cctype>
#include <locale>
#include <codecvt>

#include <array>

namespace search {

// loc_("ru_RU.UTF-8")
class StemmingImpl {
public:
	explicit StemmingImpl(const std::string& path) {
		// Your code goes here..
		// Think about fork and pipe
	}

	std::string Process(const std::string& word) {
		return word;
	}


	~StemmingImpl() {
		// Your code goes here...
		// Clean up all
	}

private:
	// Your code goes here...
};

}