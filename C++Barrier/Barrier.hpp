/*	C++ 11 Thread barrier class
*	Written by Henrik Lee Jotun and Johannes Hovland
*	2014.12.05
*/

#pragma once
#include <mutex>
#include <atomic>
#include <condition_variable>
//#include <ctime>
//#include <chrono>

#include <stdio.h>

class Barrier {
public:
	Barrier();
	Barrier(int maxThreads);
	~Barrier();

	//Waits for a signal
	void wait();

	//Waits for a signal or some duration. Returns true on signal, false on timeout.				
	//bool waitUntil(int waitForMs);

	//Sends a signal allowing other threads to continue
	void signal();

private:
	int maxWaitingThreads;
	std::atomic<int> waitingThreads;
	std::mutex lock;
	std::condition_variable cv;
	//bool flag;
};