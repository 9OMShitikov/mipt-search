#pragma once

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocketImpl.h>
#include <Poco/Util/ServerApplication.h>

#include "lib/common/config.h"
#include "lib/server/index/storage.h"

namespace search {

class ServerSocketImpl : public Poco::Net::ServerSocketImpl {
   public:
	using Poco::Net::SocketImpl::init;
};

class Socket : public Poco::Net::Socket {
   public:
	explicit Socket(const std::string &address);
};

class NetworkServer : public Poco::Util::ServerApplication {
   public:
	int main(const std::vector<std::string> &args);

	virtual void defineOptions(Poco::Util::OptionSet &options);

	void handleConfig(const std::string &name, const std::string &value);

   private:
	std::shared_ptr<SearchConfig> m_pConfig;
};

}  // namespace search