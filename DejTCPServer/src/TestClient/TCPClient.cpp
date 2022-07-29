/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio tcp client sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#include "TestClient/TCPClient.h"
#include "TCPServer/TCPData.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

TCPClient::TCPClient(boost::asio::io_service& svc, std::string const& host, std::string const& port)
	: m_ioservice(svc),m_socket(svc)
{
	boost::asio::ip::tcp::resolver resolver(m_ioservice);
	boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query(host, port));
	boost::asio::connect(this->m_socket, endpoint);
	m_dbuf.clear();
}

//If empty input this will send a stock message, else the formatted hex message
void TCPClient::sendHexMessage(DBuffer* buf, tcpser::uint8_t times)
{
	if (!(*buf).size()) {
		tcpser::uint8_t arr[] = { 0xE1, 0x10, 0x00, 0x00, 0x00, 0x00, \
			0xDA, 0x7A, 0x00, 0x00, 0x00, 0x05, 0x010, \
			0x20, 0x30, 0x40, 0x50, 0x0B, 0x1E, 0x00, \
			0x00, 0x00, 0x00 };

		DBuffer m_data(arr, arr + (sizeof(arr) / sizeof(arr[0])));
		buf = &m_data;
	}

	for (int i = 0; i < times; i++) {
		m_socket.send(boost::asio::buffer(*buf));
		printf("Sending %d\n", i);
		boost::this_thread::sleep_for(boost::chrono::seconds(10));
	}
}

DBuffer* TCPClient::formatHexMessage(tcpser::uint16_t type, tcpser::uint32_t length, std::string message)
{	
	m_dbuf.clear();
	tcpser::uint32_t cursize = 6 + length;
	if (cursize >= 0xEFFFFFFF) {
		printf("Invalid size for the buffer. Not processing..\n");
		m_dbuf.clear();
		return &m_dbuf;
	}
	m_dbuf.resize(6 + length);
	fill(m_dbuf.begin(), m_dbuf.end(), 0);
	m_dbuf[0] = (type >> 8) & 0xFF; 
	m_dbuf[1] = type & 0xFF;
	m_dbuf[2] = (length >> 24) & 0xFF;
	m_dbuf[3] = (length >> 16) & 0xFF;
	m_dbuf[4] = (length >> 8) & 0xFF;
	m_dbuf[5] = length & 0xFF;
	int bof = 6; //buffer offset
	//insert the message as it is till the length rest are 0
	const char* msgbuf = message.c_str();
	tcpser::uint32_t actualLength = message.size();
	//we fill only the available string vals. rest are 0
	for (int i = 0; i < length; i++) {
		if (i < actualLength) {
			m_dbuf[bof+i]= (msgbuf[i]);
		}
		else {
			break;
		}
	}
	return &m_dbuf;
}

//run a battery of tests to break the server
void TCPClient::stressTestServer()
{
	DBuffer* mb = formatHexMessage(HELLO, 0xFFFFFFF, "ST1 Stress test1");
	sendHexMessage(mb,1);
	mb->clear();
	mb = formatHexMessage(DATA, 0xEFFFFFF, "ST2 Stress test2");
	sendHexMessage(mb,8);
	mb->clear();
	mb = formatHexMessage(BYE, 0xFF, "ST3 Stress test3");
	sendHexMessage(mb, 4);
	mb->clear();
	mb = formatHexMessage(BYE, 0xEFF, "ST3 Stress test3");	
	sendHexMessage(mb, 1);
	//Send alex custom message
	mb->clear();
	mb = formatHexMessage(ALEX, 0x123, "ALEX Stress test5");
	sendHexMessage(mb, 5);	
	//send empty message with invalid length. This will lead closing the connection by host
	mb->clear();
	tcpser::uint8_t arr[] = { 0xE1, 0x10, 0x00, 0x00, 0x00, 0x00, \
		0xDA, 0x7A, 0xFF, 0xFF, 0xFF, 0xFF, 0x010, \
		0x20, 0x30, 0x40, 0x50, 0x0B, 0x1E, 0x00, \
		0x00, 0x00, 0x00 };
	for (int i = 0; i < sizeof(arr); i++) {
		mb->push_back(arr[i]);
	}
	sendHexMessage(mb, 3);
	mb->clear();
}

//we send only fixed hex buffer. But it can be modified to send string buffer too.
void TCPClient::send(std::string const& message) 
{
	printf("%s",message.c_str());
	stressTestServer();
	DBuffer* mb = formatHexMessage(HELLO, 0xFFFFFFF, "This is a test");
	sendHexMessage(mb,1);
	//m_socket.send(boost::asio::buffer(message));
}

//thread run override
void TCPClient::run()
{
	printf("TCPClient thread enter.\n");
	try {
		send("Do the stress tests.\n");
	}
	catch (std::exception & e) {
		printf("Client exception: %s", e.what());
	}
}

//for future expansion. Currently we don't read anything
void TCPClient::read() 
{
	try {
		for (;;) {
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = m_socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e){
		std::cerr << e.what() << std::endl;		
	}
}


