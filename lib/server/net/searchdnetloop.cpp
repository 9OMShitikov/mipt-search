#include "searchdnetloop.h"

#include "handlers.h"

namespace search {

Socket::Socket(const std::string &address)
	: Poco::Net::Socket(new ServerSocketImpl()) {
	const Poco::Net::SocketAddress socket_address(address);
	auto socket = dynamic_cast<ServerSocketImpl *>(impl());
	socket->init(socket_address.af());
	socket->setReuseAddress(true);
	socket->setReusePort(false);
	socket->bind(socket_address, false);
	socket->listen();
}

void NetworkServer::defineOptions(Poco::Util::OptionSet &tOptions) {
	tOptions.addOption(Poco::Util::Option("config", "C")
						   .required(true)
						   .repeatable(false)
						   .argument("path")
						   .callback(Poco::Util::OptionCallback<NetworkServer>(
							   this, &NetworkServer::handleConfig)));
}

void NetworkServer::handleConfig(const std::string &name,
								 const std::string &value) {
	m_pConfig = LoadConfig(value);
}

int NetworkServer::main(const std::vector<std::string> &args) {
	// set locale
	std::locale::global(
		std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

	Poco::Net::HTTPServerParams::Ptr pParameters =
		new Poco::Net::HTTPServerParams();
	pParameters->setTimeout(100000);
	pParameters->setMaxQueued(100);
	pParameters->setMaxThreads(100);

	// load storage
	IndexStorage tStorage;
	tStorage.InitializeStorage(m_pConfig);

	const Poco::Net::ServerSocket tSocket(Socket("127.0.0.1:5849"));
	Poco::Net::HTTPServer tServer(
		new HandlerFactory(tStorage), tSocket, pParameters);

	tServer.start();
	waitForTerminationRequest();
	tServer.stopAll();

	return 0;
}

}  // namespace search