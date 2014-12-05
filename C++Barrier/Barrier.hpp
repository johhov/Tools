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

class Barrier {
public:
	Barrier();
	~Barrier();

	//Waits for a single
	void wait();
	//Waits for a single or some duration. Returns true on signal, false on timeout.				
	//bool waitFor(int waitForMs);
	void signal();

private:
	std::mutex lock;
	std::condition_variable cv;
	//bool flag;
};