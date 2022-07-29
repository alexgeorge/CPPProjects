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


using boost::asio::ip::tcp;

//this is a driver for testing the TCPServer. 
int main(int argc, char* argv[])
{
	try{
		if (argc != 3){
			std::cerr << "Usage: client <host> <port>" << std::endl;
			return 1;
		}		
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		TCPClient tc(io_service, argv[1], argv[2]);
		tc.start();
		tc.join();
	}
	catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	return 0;
}