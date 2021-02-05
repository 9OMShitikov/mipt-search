#include <iostream>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

#include "cmdparser.h"
#include "variadic_table.h"

int main(int argc, char* argv[]) {
	Poco::Net::HTTPClientSession session("127.0.0.1", 5849);

	{
		Poco::Net::HTTPRequest request("GET", "/ping");
		session.sendRequest(request);
		Poco::Net::HTTPResponse response;
		session.receiveResponse(response);

		if (response.getStatus() != 200) {
			std::cerr << "Can't connect to server" << std::endl;
			return -1;
		}
	}

	CommandLineParser parser(std::cin, std::cout);
	while (parser.Parse()) {
		if (parser.IsCompleted()) {
			// Your code goes here...

			std::string error;

			if (!error.empty()) {
				std::cerr << error << std::endl;
			} else {
				VariadicTable<std::string, std::string> vt({"document_id", "weight"}, 10);

				// Your code goes here...
			}
		}
	}

	return 0;
}