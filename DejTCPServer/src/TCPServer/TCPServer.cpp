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

namespace tcpser
{

	TCPServer::TCPServer(boost::asio::io_service& io_service, uint16_t port)
			: m_acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
			m_port(port)
	{
		startAccept();
	}

	void TCPServer::startAccept()
	{
		//Calling the static function in the connection to spawn a shared pointer
		//This will help the garbage collection and hence manage the object instances
		TCPConnection::TCPConnectionPtr new_connection = TCPConnection::create(m_acceptor.get_io_service());
	
		//bind the function which is handling the connection
		m_acceptor.async_accept(new_connection->socket(),boost::bind(&TCPServer::handleAccept, this, new_connection, boost::asio::placeholders::error));
	}

	void TCPServer::handleAccept(TCPConnection::TCPConnectionPtr new_connection, const boost::system::error_code& error)
	{
		if (!error){
			//whenever a new client is connected to the server we create
			//a new connection and handover the handling to that connection
			//this way multiple connections are allowed 
			new_connection->start();
		}
		startAccept();
	}

	void TCPServer::run()
	{
		printf("TCPserver thread enter.\n");
		try {
			m_acceptor.get_io_service().run();
		}
		catch (std::exception & e) {
			printf("TCPServer exception: %s", e.what());
		}
	}


} //tcpser