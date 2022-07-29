/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio tcp client sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include "TestClient/BThread.h"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
typedef std::vector<uint8_t> DBuffer;
using namespace tcpser;

class TCPClient : public tcpser::Thread
{
	
	public:
		//CTOR
		//the io_service is to be initialised in the ctor, else there will be errors
		TCPClient(boost::asio::io_service& svc, std::string const& host, std::string const& port);

		//we send only hex buffer
		void send(std::string const& message);

		//place holder. Can be extended
		void read();

		//support function for testing
		void sendHexMessage(DBuffer* buf, uint8_t times);

		//stress test the server
		void stressTestServer();

		//Format a string to hexmessage with specified header and length
		DBuffer* formatHexMessage(uint16_t type, uint32_t length, std::string message);

	protected:
		//override the thread run
		void run();

	private:
		DBuffer m_dbuf;
		boost::asio::ip::tcp::socket m_socket;
		boost::asio::io_service& m_ioservice;
};

#endif //_TCP_CLIENT_H_