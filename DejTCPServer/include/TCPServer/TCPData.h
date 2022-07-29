/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::asio sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/
#ifndef _TCP_DATA_H_
#define _TCP_DATA_H_


#include <string>
#include <vector>
#include <stdio.h>

namespace tcpser
{

	typedef signed char        int8_t;
	typedef short              int16_t;
	typedef int                int32_t;
	typedef long long          int64_t;
	typedef unsigned char      uint8_t;
	typedef unsigned short     uint16_t;
	typedef unsigned int       uint32_t;
	typedef unsigned long long uint64_t;

	typedef std::vector<uint8_t> DataBuffer;

	//TLV sizes to be read
	const unsigned TYPE_SIZE = 2;
	const unsigned LENGTH_SIZE = 4;
	const unsigned VALUE_SIZE = 4;
	const unsigned headerLength = TYPE_SIZE + LENGTH_SIZE;

#define HELLO	0xE110
#define DATA	0xDA7A
#define BYE		0x0B1E
#define ALEX	0xA1EC
#define INVALID	0xABCD

	//generic function to show hex output
	template <class CharContainer>
	std::string showHex(const CharContainer& c)
	{
		std::string hex;
		char buf[16];
		typename CharContainer::const_iterator i;
		for (i = c.begin(); i != c.end(); ++i) {
			sprintf(buf, "0x%02X ", (*i));
			hex += buf;
		}
		return hex;
	}

	typedef struct _strTLV{
		uint32_t length;
		uint16_t type;
		std::string stype;
		std::string slength;
		std::string svalue;
		std::string srcIP;
		unsigned short srcPort;
	}tlvStruct;

	class TCPData 
	{
	public :
		
		//ctor init with ip and port
		TCPData(std::string srcip, uint16_t srcport);
		
		//dtor
		virtual ~TCPData() {};
		
		//returns the struct with information about length
		tlvStruct* parseHeader(DataBuffer &buf);

		//parse the body. Call it only if the header has valid length
		tlvStruct* parseData(DataBuffer &buf);

		//display the output to terminal
		void showOutput();

	private:
		tlvStruct m_tlvStr;
		std::string m_srcip;
		uint16_t m_srcport;
	};


} //tcpser

#endif //_TCP_DATA_H_
