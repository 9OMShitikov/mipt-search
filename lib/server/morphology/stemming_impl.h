#pragma once

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <cctype>
#include <codecvt>
#include <locale>
#include <vector>

#include "lib/std/string.h"

namespace search {

// loc_("ru_RU.UTF-8")
class StemmingImpl {
   public:
	explicit StemmingImpl(const std::string &path) {
		// Your code goes here..
		// Think about fork and pipe
	}

	std::string Process(const std::string &word) { return word; }

	~StemmingImpl() {
		// Your code goes here...
		// Clean up all
	}

   private:
	// Your code goes here...
};

}  // namespace search