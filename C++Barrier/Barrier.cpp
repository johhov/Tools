/*	
*	C++ 11 Thread barrier class
*	Written by Johannes Hovland (johannes.hovland@gmail.com)
*	2014.12.05
*/

#include "Barrier.hpp"

Barrier::Barrier() {
	maxWaitingThreads = 0;
	waitingThreads = 0;
	signalSent = false;
}

Barrier::Barrier(int maxThreads) {
	maxWaitingThreads = maxThreads;
	
	waitingThreads = 0;
	signalSent = false;
}

Barrier::~Barrier() {

}

void Barrier::wait() {
	if(checkForMaxWaitingThreads()) {
		waitingThreads--;
		signal();
		return;
	}

	std::unique_lock<std::mutex> l(lock);
	cv.wait(l);

	std::atomic_thread_fence(std::memory_order_acquire);

	if(maxWaitingThreads) {
		waitingThreads--;
	}
}

bool Barrier::waitUntil(int waitForMs) {
	signalSent = false;

	if(checkForMaxWaitingThreads()) {
		waitingThreads--;
		signal();
		return signalSent;
	}

	std::unique_lock<std::mutex> l(lock);
	auto now = std::chrono::system_clock::now();
	cv.wait_until(l, (now + std::chrono::milliseconds(waitForMs)), [&](){return signalSent;});

	std::atomic_thread_fence(std::memory_order_acquire);

	if(maxWaitingThreads) {
		waitingThreads--;
	}

	return signalSent;
}

void Barrier::signal() {
	signalSent = true;
	std::atomic_thread_fence(std::memory_order_release);
	cv.notify_all();
}

bool Barrier::checkForMaxWaitingThreads() {
	if(maxWaitingThreads > 0){
		waitingThreads++;

		if(waitingThreads >= maxWaitingThreads) {
			return true;
		}
	}

	return false;
}