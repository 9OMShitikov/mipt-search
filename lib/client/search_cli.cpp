#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/URI.h>

#include <iostream>

#include "cmdparser.h"
#include "variadic_table.h"

int main(int argc, char * argv[])
{
	Poco::Net::HTTPClientSession session("127.0.0.1", 5849);

	{
		Poco::Net::HTTPRequest request("GET", "/ping");
		session.sendRequest(request);
		Poco::Net::HTTPResponse response;
		session.receiveResponse(response);

		if (response.getStatus() != 200)
		{
			std::cerr << "Can't connect to server" << std::endl;
			return -1;
		}
	}

	CommandLineParser parser(std::cin, std::cout);
	while (parser.Parse())
	{
		if (parser.IsCompleted())
		{
			Poco::Net::HTTPRequest request("GET", "/sql_command", Poco::Net::HTTPMessage::HTTP_1_1);
			request.setContentLength(parser.GetQuery().size());
			request.setContentType("text/html;charset=utf-8");
			std::ostream& out = session.sendRequest(request);
			out << parser.GetQuery() << std::endl;

			Poco::Net::HTTPResponse response;
			std::istream& in = session.receiveResponse(response);

			Poco::JSON::Parser parser;
			Poco::JSON::Object::Ptr response_json = parser.parse(in).extract<Poco::JSON::Object::Ptr>();

			std::string error = response_json->get("error").extract<std::string>();
			if (!error.empty())
			{
				std::cerr << error << std::endl;
			} else
			{
				Poco::Dynamic::Array table = *response_json->getArray("data");
				VariadicTable<std::string, std::string> vt(
					{ "document_id", "weight" }, 10);

				for (int i = 0; i < table.size(); ++i) {
					vt.addRow(table[i]["document_id"], table[i]["weight"]);
				}

				std::cout<<std::endl;
				vt.print(std::cout);
			}
		}
	}

	return 0;
}