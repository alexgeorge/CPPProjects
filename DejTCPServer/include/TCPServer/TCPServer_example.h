#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <iostream>
#include <stdlib.h>

#ifdef __RT_WINDOWS__
#pragma warning(default: 4267)
#endif
#include <boost/bind.hpp>


#if 0

class ApiServer 
{
public:
	//! !ctor
	ApiServer( boost::asio::io_service & ioService, char const * netAddr, short netPort);

	//! connect new client
	void connect(const ClientPtr & client);

	//! disconnect existing client
	void disconnect(const ClientPtr & client);

	//! new data received
	bool process(const ClientPtr & client, const DataBuffer & input, DataBuffer & output);

	//! quit server
	virtual void quit(bool joinThread = true);

protected:
	//! accept a new client
	void acceptNewClient();

	//! handling the acceptance of a new client
	void handleNewClientAccept(const SocketClientPtr & client, const boost::system::error_code & error);

	//! io server thread
	virtual void run();

protected:
	boost::asio::ip::tcp::acceptor m_acceptor;

};

#endif //0

#endif // _TCP_SERVER_H_ 
