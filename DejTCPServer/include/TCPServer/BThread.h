/*
Purpose:- For Dejero ......
Developer:- Alex George alexvgeorge@gmail.com
Date:- December 23 2017
Inspiration:- Based on boost::thread sample code
Compiled and tested in :- Ubuntu 16.04 and Windows10 (using VC++ 2015)
Dependencies:- boost libraries
Distribution:- No strings attached. Use at your own risk.
*/

#ifndef _B_THREAD_H_
#define _B_THREAD_H_

#include <string>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

namespace tcpser
{

	class Thread
	{

	private:
		typedef boost::shared_ptr<boost::thread> ThreadPtr;
	
	public:
		Thread();
		virtual ~Thread() { }
		bool	cancel();
		bool	isRunning() const;
		void	join();
		virtual void quit(bool joinThread = true);
		bool	start();
		bool	testCancel() const;

	protected:
		//override this to use this as base
		virtual void run() = 0;
		void runWrapper();

	private:
		volatile bool	m_cancelling;
		mutable boost::mutex m_mutex;
		volatile bool	m_running;
		ThreadPtr	m_thread;
	};

}	// namespace tcpser

#endif  // _B_THREAD_H_ 
