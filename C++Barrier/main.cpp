//Test program for the Barrier class

#include <unistd.h>
#include <thread>
#include <stdio.h>

#include "Barrier.hpp"

const int THREADS = 10;


void doWork(int i) {
	usleep(10000*i);
}

void processData(int threadNumber, Barrier* barrier) {
	doWork(threadNumber);
	printf("Thread number %d waiting.\n", threadNumber);
	barrier->wait();
	printf("Thread number %d Finished.\n", threadNumber);
}

int main (int argc, char* argv[]) {
	std::thread threadPool[THREADS];
	Barrier barrier(THREADS);

	for (int i = 0; i < THREADS; i++) {
		threadPool[i] = std::thread(processData, i, &barrier);
	}


	for (auto& thread : threadPool) {
		thread.join();
	}

	return 0;
}