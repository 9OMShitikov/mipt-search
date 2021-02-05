#pragma once

#include <string>
#include <istream>
#include <ostream>

class CommandLineParser {
public:
	explicit CommandLineParser(std::istream& in, std::ostream& out);

	bool Parse();
	bool IsCompleted() const;
	std::string GetQuery() const;

private:
	std::istream& in_;
	std::ostream& out_;

	std::string buffer_;
	bool completed_line_ = true;

	std::string query_;
};
