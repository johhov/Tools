#include <unistd.h>
#include <thread>
#include <stdio.h>

#include "Barrier.hpp"

const int THREADS = 5;


void doWork() {
	usleep(50000);
}

void processData(int threadNumber, Barrier* barrier) {
	printf("Thread number %d waiting.\n", threadNumber);
	barrier->wait();
	printf("Thread number %d Finished.\n", threadNumber);

	printf("Thread number %d waiting.\n", threadNumber);
	barrier->wait();
	printf("Thread number %d Finished.\n", threadNumber);
}

int main (int argc, char* argv[]) {
	std::thread threadPool[THREADS];
	Barrier barrier;

	for (int i = 0; i < THREADS; i++) {
		threadPool[i] = std::thread(processData, i, &barrier);
	}

	doWork();
	barrier.signal();
	printf("Signaling\n");
	
	doWork();
	barrier.signal();
	printf("Signaling\n");

	for (auto& thread : threadPool) {
		thread.join();
	}

	return 0;
}