/*	C++ 11 Thread barrier class
*	Written by Henrik Lee Jotun and Johannes Hovland
*	2014.12.05
*/

#include "Barrier.hpp"

Barrier::Barrier() {
	//flag = ATOMIC_VAR_INIT(0);
}

Barrier::~Barrier() {

}

void Barrier::wait() {
	std::unique_lock<std::mutex> l(lock);
	cv.wait(l);

	std::atomic_thread_fence(std::memory_order_acquire);
}
/*
bool Barrier::waitFor(int waitForMs) {
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
	
	cv.notify_all();

	std::atomic_thread_fence(std::memory_order_release);
}