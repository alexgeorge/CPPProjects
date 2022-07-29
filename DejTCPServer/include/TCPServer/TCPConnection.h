/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio tcp server sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#ifndef _TCP_CONNECTION_H_
#define _TCP_CONNECTION_H_

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "TCPServer/TCPData.h"

using boost::asio::ip::tcp;

namespace tcpser
{

	class TCPConnection
		: public boost::enable_shared_from_this<TCPConnection>
	{
	public:
		//use smart pointers for garbage collection
		typedef boost::shared_ptr<TCPConnection> TCPConnectionPtr;
		typedef boost::shared_ptr<TCPData> TCPDataPtr;

		//static function which spawns the reading using io_service 
		static TCPConnectionPtr create(boost::asio::io_service& io_service);

		//Share the socket with caller
		tcp::socket& socket();

		//starct connection and accept messages
		void start();

		//read from socket
		void readMessage();

		//process the received message
		void processMessage(const boost::asio::streambuf &msg);

		//write to socket. For future expansion
		void sendMessage();

		//close the socket and exit
		void quit();

	private:
		TCPConnection(boost::asio::io_service& io_service);

		//for future expansion
		void handleWrite(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

		//read the header from the stream Type + length fields
		void startReadHeader();

		//read the value from the buffer
		void startReadBody(unsigned int msgLen);

		//callback for the startReadHeader
		void handleReadHeader(const boost::system::error_code & error);

		//callback for the startReadBody
		void handleReadBody(const boost::system::error_code & error);

		tcp::socket m_socket;
		std::string m_message;
		std::string m_sourceip;
		uint16_t m_sourceport;
		TCPDataPtr m_dataptr;
		DataBuffer m_readBuf;
		uint32_t m_bytesToRead;
		uint32_t m_readBytes;
	};

} //tcpser

#endif //_TCP_CONNECTION_H_