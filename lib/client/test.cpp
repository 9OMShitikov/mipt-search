#include <catch.hpp>
#include <sstream>

#include "cmdparser.h"

TEST_CASE("(CMDParser) Basic commands")
{
	std::string query = "SELECT * FROM rt;";

	std::stringstream in(query), out;
	CommandLineParser parser(in, out);

	REQUIRE(!parser.IsCompleted());
	REQUIRE(parser.Parse());
	REQUIRE(parser.IsCompleted());

	REQUIRE(parser.GetQuery() == "SELECT * FROM rt;");
	REQUIRE(out.str() == "mipt-search> ");

	REQUIRE(!parser.Parse());
	REQUIRE(!parser.IsCompleted());
}

TEST_CASE("(CMDParser) Several lines")
{
	std::string query =
		"SELECT *\n"
		"FROM rt\n"
		"WHERE id > 10;";

	std::stringstream in(query), out;
	CommandLineParser parser(in, out);

	REQUIRE(!parser.IsCompleted());
	REQUIRE(parser.Parse());
	REQUIRE(!parser.IsCompleted());
	REQUIRE(parser.Parse());
	REQUIRE(!parser.IsCompleted());
	REQUIRE(parser.Parse());
	REQUIRE(parser.IsCompleted());

	REQUIRE(parser.GetQuery() == "SELECT * FROM rt WHERE id > 10;");
	REQUIRE(out.str() == "mipt-search> > > ");

	REQUIRE(!parser.Parse());
	REQUIRE(!parser.IsCompleted());
}

TEST_CASE("(CMDParser) One line several queries")
{
	std::string query = "SELECT *;SELECT *;";

	std::stringstream in(query), out;
	CommandLineParser parser(in, out);

	REQUIRE(!parser.IsCompleted());
	REQUIRE(parser.Parse());
	REQUIRE(parser.IsCompleted());

	REQUIRE(parser.GetQuery() == "SELECT *;");
	REQUIRE(out.str() == "mipt-search> ");

	REQUIRE(parser.Parse());

	REQUIRE(parser.IsCompleted());
	REQUIRE(parser.GetQuery() == "SELECT *;");

	REQUIRE(out.str() == "mipt-search> mipt-search> ");

	REQUIRE(!parser.Parse());
	REQUIRE(!parser.IsCompleted());
}

TEST_CASE("(CMDParser) One line several queries 2")
{
	std::string query = "SELECT *;SELECT *";

	std::stringstream in(query), out;
	CommandLineParser parser(in, out);

	REQUIRE(!parser.IsCompleted());
	REQUIRE(parser.Parse());
	REQUIRE(parser.IsCompleted());

	REQUIRE(parser.GetQuery() == "SELECT *;");
	REQUIRE(out.str() == "mipt-search> ");

	REQUIRE(!parser.Parse());
	REQUIRE(!parser.IsCompleted());
}

TEST_CASE("(CMDParser) Query ending with \n")
{
	std::string query = "SELECT *;\n";

	std::stringstream in(query), out;
	CommandLineParser parser(in, out);

	REQUIRE(parser.Parse());
	REQUIRE(parser.IsCompleted());

	REQUIRE(parser.GetQuery() == "SELECT *;");
	REQUIRE(out.str() == "mipt-search> ");

	REQUIRE(!parser.Parse());
	REQUIRE(!parser.IsCompleted());
}
