#include "driver.hh"
#include "parser.hh"

Driver::Driver() :
		trace_parsing(false),
		trace_scanning(false),
		scanner(*this), parser(scanner, *this) {
}


std::shared_ptr<Ast> Driver::Parse(const std::string& query) {
	location.initialize(&query);

	ScanBegin(query);

	parser.set_debug_level(trace_parsing);
	parser();
	ScanEnd();

	return parsed;
}

void Driver::ScanBegin(const std::string& query) {
	scanner.set_debug(trace_scanning);

	input = std::stringstream(query);
	scanner.yyrestart(&input);
}

void Driver::ScanEnd()
{
}
