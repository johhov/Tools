/*	
*	C++ 11 Thread barrier class
*	Written by Johannes Hovland (johannes.hovland@gmail.com)
*	2014.12.05
*/

#pragma once
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>

class Barrier {
public:
	Barrier();
	Barrier(int maxThreads);
	~Barrier();

	/*
	*	If default constructor was used:
	*		Waits for a signal.
	*	If maxWaitingThreads was defined:
	*		Waits for a signal or untill maxWaitingThreads number of
	*		threads reach the barrier.
	*	If maxThreads was defined as 0:
	*		Use default behaviour.
	*/
	void wait();

	/*
	*	Waits for a signal or for a number of milliseconds
	*	which ever comes first.
	*
	*	Returns true on signal, false on timeout.				
	*/
	bool waitUntil(int waitForMs);

	/*
	*	Sends a signal allowing the current and other threads to continue.
	*/
	void signal();

	/*
	*	If maxWaitingThreads is set, increment waitingThreads.
	*	Check to see if limmit has been reached.
	*/
	bool checkForMaxWaitingThreads();

private:
	int maxWaitingThreads;
	std::atomic<int> waitingThreads;
	std::mutex lock;
	std::condition_variable cv;
	bool signalSent; 
};