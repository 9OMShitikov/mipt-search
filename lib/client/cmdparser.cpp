#include "cmdparser.h"

CommandLineParser::CommandLineParser(std::istream & in, std::ostream & out)
	: in_(in)
	, out_(out)
{}

bool CommandLineParser::Parse()
{
	if (buffer_.empty() || IsCompleted())
	{
		out_ << "mipt-search> ";
	} else
	{
		out_ << "> ";
	}

	if (IsCompleted())
	{
		query_ = "";
	}

	if (completed_line_) {
		std::string new_line;
		std::getline(in_, new_line);

		if (new_line.empty())
		{
			if (in_.eof())
			{
				return false;
			}
		}

		if (!buffer_.empty())
		{
			buffer_ += " ";
		}

		buffer_ += new_line;
	}

	std::size_t delimiter_pos = buffer_.find(';');
	if (delimiter_pos == std::string::npos) {
		completed_line_ = true;
		return true;
	}

	query_ = buffer_.substr(0, delimiter_pos + 1);
	buffer_ = buffer_.substr(delimiter_pos + 1);
	completed_line_ = (buffer_.find(";") == std::string::npos);
	return true;
}

bool CommandLineParser::IsCompleted() const
{
	return !query_.empty();
}

std::string CommandLineParser::GetQuery() const
{
	return query_;
}
