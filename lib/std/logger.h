#pragma once

#include <sys/stat.h>

#include <iostream>

#define UNUSED(var) (void)var

#define logInfo(msg) std::cerr << "[INFO] " << msg << '\n';

#define logWarning(msg) std::cerr << "[WARNING] " << msg << '\n';

#define logError(msg) std::cerr << "[ERROR] " << msg << '\n';

#define logFatal(msg)                       \
	std::cerr << "[FATAL] " << msg << '\n'; \
	exit(1);

inline bool IsFileExisting(const std::string &sPath) {
	struct stat buffer;
	return (stat(sPath.c_str(), &buffer) == 0);
}
