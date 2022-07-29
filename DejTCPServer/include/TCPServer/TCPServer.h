/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio tcp server sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "TCPServer/TCPConnection.h"
#include "TCPServer/BThread.h"

using boost::asio::ip::tcp;

namespace tcpser
{

	class TCPServer : public Thread
	{
	public:
		//ctor
		TCPServer(boost::asio::io_service& io_service, unsigned short port);

	protected:
		// server thread
		virtual void run();

		//start the socket and accept connection
		void startAccept();

		//process handle
		void handleAccept(TCPConnection::TCPConnectionPtr new_connection, const boost::system::error_code& error);

		tcp::acceptor m_acceptor;
		unsigned short m_port;
	
	};

} //tcpser

#endif //_TCP_SERVER_H_