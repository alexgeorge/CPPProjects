/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::thread sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#include "TCPServer/BThread.h"

#include <boost/make_shared.hpp>

namespace tcpser
{

	Thread::Thread()
	{
		m_running = false;
		m_cancelling = false;
	}

	bool Thread::cancel()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		if (m_running) {
			m_cancelling = true;
		}
		return m_cancelling;
	}

	bool Thread::isRunning() const
	{
		return m_running;
	}

	void Thread::join()
	{
		if (m_thread != NULL) {
			m_thread->join();
		}
	}

	void Thread::quit(bool joinThread /*= true*/)
	{
		if (isRunning()) {
			cancel();

			if (joinThread) {
				join();
			}
		}
	}

	bool Thread::start()
	{
		boost::mutex::scoped_lock lock(m_mutex);
		if (!m_running) {
			m_running = true;
			m_cancelling = false;
			m_thread = boost::make_shared<boost::thread>(boost::bind(&Thread::runWrapper, this));
			return true;
		}
		else {
			return false;
		}
	}

	bool Thread::testCancel() const
	{
		return m_cancelling;
	}

	void Thread::runWrapper()
	{
		run();
		{
			boost::mutex::scoped_lock lock(m_mutex);
			m_running = false;
			m_cancelling = false;
		}
	}

}	// namespace tcpser  
