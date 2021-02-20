#pragma once

#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "parser.hh"
#include "scanner.h"

class Driver {
   public:
	Driver();

	std::shared_ptr<Ast> Parse(const std::string &f);
	void ScanBegin(const std::string &query);
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
