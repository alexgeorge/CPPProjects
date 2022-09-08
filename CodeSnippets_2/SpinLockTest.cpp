/**
 * @file SpinLockTest.cpp
 * @author alexvgeroge@vaxel.com
 * @brief The purpose of a spin lock is to prevent multiple threads from concurrently 
 * accessing a shared data structure. In contrast to a mutex, threads will busy-wait 
 * and waste CPU cycles instead of yielding the CPU to another thread.
 * 
 * @version 0.1
 * @date 2022-09-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief We will need an atomic way to determine if the lock is currently free or in use, 
 * atomic means it is guaranteed to be isolated from other operations that may be 
 * happening at the same time.
 * Ref - https://en.cppreference.com/w/cpp/atomic/atomic_flag
 */

#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <chrono>
 
class CSpinLock {
    private:
          std::atomic<bool> lock_ = {false};

    public:
        void lock() { while(lock_.exchange(true, std::memory_order_acquire)); }
        void unlock() { lock_.store(false, std::memory_order_release); }
};

class CSpinLockTester{
    private:
        const int max_count = 100000;
        int m_count;
        CSpinLock latch;

    public:
        CSpinLockTester() {m_count = 0;}
        virtual ~CSpinLockTester() {}
        void TestSpinLock(){
            latch.lock();
            m_count++;
			auto duration = std::chrono::milliseconds(10);
			std::this_thread::sleep_for(duration);
            latch.unlock();
            std::cout << "Counter [" << m_count << "]\n";
        }
};

int main(){

    std::vector<std::thread> thrds;
    int numWorkers = 5;
    CSpinLockTester m_tester;

    for (int i=0; i< numWorkers; ++i){
        thrds.push_back(std::move(std::thread(&CSpinLockTester::TestSpinLock, &m_tester)));
    }

    for (auto it = thrds.begin(); it !=thrds.end(); ++it){
        it->join();
    }

    return 0;
}

/**
 * @brief Semaphore or Mutex cannot be used for interrupt context in Linux Kernel. 
 * While spinlocks can be used for locking in interrupt context.
 * Deadlock vs Spinlock:- In concurrent computing, a deadlock occurs when two competing actions wait for the other to finish, 
 * and thus neither ever does.
 * Gist:-
 * Deadlock is a problem, in concurrent programming. While Spinlock is a solution for threads, 
 * so that two threads can not access the same resource at a time. 
 * Semaphores vs mutex:-
 * A Mutex is different than a semaphore as it is a locking mechanism while a semaphore is a signalling mechanism.
 * Mutex is somewhat similar binary semaphore, except it is meant for locking where as semaphore is for signaling. 
 * Semaphore will be incremented based on the number of threads
 * accessing the resource. A semaphore is fundamentally an integer whose value is never allowed to fall below 0
 * If the semaphore has value 0, the caller will be blocked (busy-waiting or more likely on a queue) until the semaphore 
 * has a value larger than 0, and then it is decremented by 1.
 * 
 */