#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "scanner.h"
#include "parser.hh"

class Driver {
public:
	Driver();

	std::shared_ptr<Ast> Parse(const std::string& f);
	void ScanBegin(const std::string& query);
	void ScanEnd();

	friend class Scanner;

	std::shared_ptr<Ast> parsed;

private:
	bool trace_parsing;
	bool trace_scanning;
	yy::location location;

	Scanner scanner;
	yy::parser parser;

	std::stringstream input;
};
