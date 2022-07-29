/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio tcp server sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#include "TCPServer/TCPServer.h"

using namespace tcpser;

void server_thread() {
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13));

		{
			boost::asio::ip::tcp::socket socket(io_service);
			acceptor.accept(socket);

			boost::asio::streambuf sb;
			boost::system::error_code ec;
			while (boost::asio::read(socket, sb, ec)) {
				std::cout << "received: '" << &sb << "'\n";

				if (ec) {
					std::cout << "status: " << ec.message() << "\n";
					break;
				}
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

#include <boost/thread.hpp>

int main1() {
	boost::thread_group tg;
	tg.create_thread(server_thread);

	boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	//tg.create_thread(client_thread);

	tg.join_all();
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cerr << "Usage: server <port>" << std::endl;
		return 1;
	}
	tcpser::uint16_t port = (tcpser::uint16_t)strtoul(argv[1], NULL, 0);
	try
	{
		boost::asio::io_service io_service;
		TCPServer server(io_service,port);
		//io_service.run();
		server.start();
		server.join();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}