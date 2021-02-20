#include "cmdparser.h"

CommandLineParser::CommandLineParser(std::istream &in, std::ostream &out)
	: in_(in), out_(out) {}

bool CommandLineParser::Parse() {
	// Your code goes here...

	return true;
}

bool CommandLineParser::IsCompleted() const { return !query_.empty(); }

std::string CommandLineParser::GetQuery() const { return query_; }
