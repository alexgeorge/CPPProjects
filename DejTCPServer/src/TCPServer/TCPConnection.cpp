/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio tcp server sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/
#include "TCPServer/TCPConnection.h"

namespace tcpser
{
	//ctor. Need initialisation of io_service in ctor
	TCPConnection::TCPConnection(boost::asio::io_service& io_service)
		: m_socket(io_service),
		m_bytesToRead(headerLength),
		m_readBytes(0)
	{
			
	}

	//static function which creates a shared pointer and manage the instance
	TCPConnection::TCPConnectionPtr TCPConnection::create(boost::asio::io_service& io_service)
	{
		return TCPConnectionPtr(new TCPConnection(io_service));
	}

	tcp::socket& TCPConnection::socket()
	{
		return m_socket;
	}

	//starting function for the client communication
	void TCPConnection::start()
	{
		//get the source ip address and port number
		m_sourceip = m_socket.remote_endpoint().address().to_string();
		m_sourceport = m_socket.remote_endpoint().port();
		//we are using a shared pointer for data object
		m_dataptr.reset(new TCPData(m_sourceip, m_sourceport));	
		//readMessage(); //sync read
		printf("Creating a new connection to port %d from server %s \n",m_sourceport,m_sourceip.c_str());
		startReadHeader(); //async_read operation
	}

	//this function uses sync read. Not used currently 
	void TCPConnection::readMessage()
	{
		boost::asio::streambuf sb;
		boost::system::error_code ec;
		while (boost::asio::read(m_socket, sb, ec)) {			
			processMessage(sb);
			//std::cout << "received: '" << &sb << "'\n";
			if (ec) {
				std::cout << "status: " << ec.message() << "\n";
				break;
			}
		}		
	}

	//Read the header and length field. If there are errors we dont proceed.
	void TCPConnection::startReadHeader()
	{		
		m_readBuf.resize(headerLength);
		boost::asio::mutable_buffers_1 buf = boost::asio::buffer(&m_readBuf[headerLength-m_bytesToRead], headerLength);
		boost::asio::async_read(m_socket, buf, boost::bind(&TCPConnection::handleReadHeader, shared_from_this(), boost::asio::placeholders::error));
	}

	//we read only 4 bytes of the body and skip the rest. This should be extended to make use of the message in body
	void TCPConnection::startReadBody(unsigned int msgLen)
	{
		m_readBuf.resize(headerLength + msgLen);
		boost::asio::mutable_buffers_1 buf = boost::asio::buffer(&m_readBuf[headerLength], msgLen);
		boost::asio::async_read(m_socket, buf, boost::bind(&TCPConnection::handleReadBody, shared_from_this(), boost::asio::placeholders::error));
	}

	//call back function bound to the startReadHeader
	void TCPConnection::handleReadHeader(const boost::system::error_code & error)
	{
		if (!error) {			
			unsigned int msglen = 0;
			if (m_readBuf.size() == headerLength) {
				m_bytesToRead = headerLength;
				//get the length of message
				tlvStruct* tlv = m_dataptr->parseHeader(m_readBuf);
				//validate the type values. If not matching abort operation
				if (tlv->type == HELLO || tlv->type == DATA || tlv->type == BYE || tlv->type == ALEX ){ 
					if (tlv->length) {
						//check if we are exceeding the limits set for the length+header
						if (tlv->length >= 0xFFFFFFF9) {
							printf("Invalid length. Quitting..\n");
							quit();
							return;
						}
						startReadBody(tlv->length);
					}
					else {
						m_dataptr->showOutput();
						startReadHeader();
					}				
				}
				else {
					//we dont proceed further as there are only 3 accepted types
					printf("Unknown type in header. Quitting.. \n");
					//close the socket and quit
					quit();
					return;
				}
			}
			else {
				m_bytesToRead -= (uint32_t)m_readBuf.size();
				startReadHeader();
			}
		}
		else if (error == boost::system::errc::operation_canceled) {
			return;
		}
	}

	//call back function bound to the startReadBody
	void TCPConnection::handleReadBody(const boost::system::error_code & error)
	{
		if (!error) {
			//read the 4 bytes and skip rest
			tlvStruct* tlv = m_dataptr->parseData(m_readBuf);
			//this will complete this operation so show the output and start over
			m_dataptr->showOutput();
			startReadHeader();
		}
		else if (error == boost::system::errc::operation_canceled) {
			quit();
			return;
		}
	}

	//This function is tobe removed. Not in use
	void TCPConnection::processMessage(const boost::asio::streambuf &msg)
	{		
		const char* message = boost::asio::buffer_cast<const char*>(msg.data());
		if (m_dataptr) {
			//m_dataptr->parseData(message);
		}		
		std::stringstream ss; 
		ss << m_sourceip << ":" << m_sourceport;
		std::string srcdetails = ss.str();
		printf("[%s] [%s]\n", srcdetails.c_str(), message);
	}

	//only for response testing. Not used.
	void TCPConnection::sendMessage()
	{
		boost::asio::async_write(m_socket, boost::asio::buffer(m_message),
			boost::bind(&TCPConnection::handleWrite, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	//Place holder for expansion.
	void TCPConnection::handleWrite(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/)
	{
		
	}

	//clean and quit
	void TCPConnection::quit()
	{
		boost::system::error_code ec;
		printf("Closing client socket..\n");
		m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		if (ec){
			std::cerr << "socket.shutdown error: " << ec.message() << std::endl;
		}
		m_socket.close(ec);
		if (ec){
			std::cerr << "socket.close error: " << ec.message() << std::endl;
		}	
	}

} //tcpser