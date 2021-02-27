#include "handlers.h"

#include <Poco/JSON/Object.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <sstream>

#include "lib/server/morphology/stemming.h"
#include "lib/server/net/context.h"
#include "lib/server/sql/ast.h"
#include "lib/server/sql/driver.hh"
#include "lib/std/string.h"

namespace search
{
void Ping::handleRequest(Poco::Net::HTTPServerRequest & request,
	Poco::Net::HTTPServerResponse & response)
{
	logInfo("Ping got");

	response.send().flush();
	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
}

HandleSqlCommand::HandleSqlCommand(IndexStorage & storage)
	: storage_(storage)
{
}

void HandleSqlCommand::handleRequest(Poco::Net::HTTPServerRequest & request,
	Poco::Net::HTTPServerResponse & response)
{
	char command[4096];

	request.stream().read(command, 4096);
	logInfo("Sql command: " << command);
	Poco::JSON::Object::Ptr response_json = new Poco::JSON::Object(true);

	// dummy json
	Poco::JSON::Array::Ptr data_json = new Poco::JSON::Array(true);

	Poco::JSON::Object::Ptr first_entry = new Poco::JSON::Object(true);
	first_entry->set("document_id", "1");
	first_entry->set("weight", "123");
	data_json->add(first_entry);

	first_entry = new Poco::JSON::Object(true);
	first_entry->set("document_id", "2");
	first_entry->set("weight", "124");
	data_json->add(first_entry);

	response_json->set("error", "");
	response_json->set("data", data_json);

	std::stringstream json_string;
	response_json->stringify(json_string);

	response.setContentLength(json_string.str().size());
	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
	std::ostream& resp_stream = response.send();
	response_json->stringify(resp_stream);
	resp_stream.flush();
	/** Response query **/
	// Your code goes here...

	//Driver parse_driver;
	//auto query = parse_driver.Parse(command);

	// Response error
	//if (query == nullptr)
	//{
		// Your code goes here...

		//return;
	//}

	/** Prepare query **/
	// Your code goes here...

	/** Execute query **/
	// Your code goes here...

	/** Response query **/
	// Your code goes here...

	response.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
	response.send().flush();
}

HandlerFactory::HandlerFactory(IndexStorage & storage)
	: storage_(storage)
{}

Poco::Net::HTTPRequestHandler * HandlerFactory::createRequestHandler(
	const Poco::Net::HTTPServerRequest & request)
{
	if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET)
		return nullptr;

	logInfo("Get query with endpoint: " << request.getURI());

	if (request.getURI() == "/ping")
	{
		return new Ping();
	}

	if (request.getURI() == "/sql_command")
	{
		return new HandleSqlCommand(storage_);
	}

	return nullptr;
}

} // namespace search