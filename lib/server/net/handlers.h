#pragma once

#include <memory>

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include "lib/server/index/storage.h"

namespace search {

inline std::string SyntaxError() {
	return "Syntax error";
}

inline std::string BadIndexName() {
	return "Index not found";
}

class Ping : public Poco::Net::HTTPRequestHandler {
private:
	virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

class HandleSqlCommand : public Poco::Net::HTTPRequestHandler {
public:
	explicit HandleSqlCommand(IndexStorage& storage);

private:
	virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	IndexStorage& storage_;
};

class HandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
	explicit HandlerFactory(IndexStorage& storage);

private:
	virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

private:
	IndexStorage& storage_;
};

}