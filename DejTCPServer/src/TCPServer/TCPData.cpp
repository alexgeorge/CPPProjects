/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#include "TCPServer/TCPData.h"

namespace tcpser
{
	TCPData::TCPData(std::string srcip, uint16_t srcport)
		: m_srcip(srcip),
		m_srcport(srcport)
	{
	}

	//header conatins only type and length fields
	tlvStruct*  TCPData::parseHeader(DataBuffer &buf)
	{
		int size = buf.size();
		//we have the type and length fields
		if (size == headerLength) {
			DataBuffer tempbuf( buf[0],buf[1] );
			m_tlvStr.type = buf[0] << 8 | buf[1];
			m_tlvStr.stype = showHex(tempbuf);
			tempbuf.clear();
			DataBuffer::iterator i1;
			for (int i =2; i <6; i++) {
				tempbuf.push_back(buf[i]);
			}
			m_tlvStr.slength = showHex(tempbuf);
			m_tlvStr.length = buf[2] << 24 | buf[3] << 16 | buf[4] << 8 | buf[5];
		}
		m_tlvStr.svalue = "";
		m_tlvStr.srcIP = m_srcip;
		m_tlvStr.srcPort = m_srcport;
		return &m_tlvStr;
	}

	//parse the body and extract only 4 bytes
	tlvStruct*  TCPData::parseData(DataBuffer &buf)
	{
		//parse only the first 4 bytes of value; which is after header bytes
		uint8_t bo = headerLength;
		if (buf.size()) {
			DataBuffer tempbuf; 
			for (int i = 0; i < 4; i++) {
				tempbuf.push_back(buf[bo + i]);
			}
			m_tlvStr.svalue = showHex(tempbuf);			
		}
		return &m_tlvStr;
	}

	//display the output in specified format
	void TCPData::showOutput()
	{
		//we display the output in the given format
		std::string type;
		if (m_tlvStr.type == HELLO) type = "Hello";
		if (m_tlvStr.type == DATA) type = "Data";
		if (m_tlvStr.type == BYE) type = "Goodbye";
		if (m_tlvStr.type == ALEX) type = "Alex";

		printf("[%s:%d] [%s] [%d] [%s]\n", m_tlvStr.srcIP.c_str(), \
			m_tlvStr.srcPort, type.c_str(), m_tlvStr.length, \
			m_tlvStr.svalue.c_str());		
	}

} //tcpser