/*	C++ 11 Thread barrier class
*	Written by Henrik Lee Jotun and Johannes Hovland
*	2014.12.05
*/

#include "Barrier.hpp"

Barrier::Barrier() {

	maxWaitingThreads = 0;
	waitingThreads = 0;
	//flag = false;
}

Barrier::Barrier(int maxWaitingThreads) {
	this.maxWaitingThreads = maxWaitingThreads;
	
	waitingThreads = 0;
	//flag = false;
}

Barrier::~Barrier() {

}

void Barrier::wait() {
	if(maxWaitingThreads > 0){
		waitingThreads++;

		if(waitingThreads >= maxWaitingThreads) {
			signal();
		}
	} else {
		std::unique_lock<std::mutex> l(lock);
		cv.wait(l);
	}

	std::atomic_thread_fence(std::memory_order_acquire);

	if(maxWaitingThreads){
		waitingThreads--;
	}
}
/*
bool Barrier::waitUntil(int waitForMs) {
	flag = false;
	std::unique_lock<std::mutex> l(lock);
	auto now = std::chrono::system_clock::now();
	
	cv.wait_until(l, now + std::chrono::milliseconds(waitFor), [&](){return flag;});

	std::atomic_thread_fence(std::memory_order_acquire);

	return flag;
}
*/
void Barrier::signal() {
	//flag = true;
	
	std::atomic_thread_fence(std::memory_order_release);
	cv.notify_all();
}