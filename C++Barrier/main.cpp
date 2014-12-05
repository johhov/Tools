//Test program for the Barrier class

#include <unistd.h>
#include <thread>
#include <stdio.h>

#include "Barrier.hpp"

const int THREADS = 10;
const int TESTS = 4;

int currentTest = 0;

std::thread threadPool[THREADS*TESTS];


void doWork(int i) {
	usleep(1000*i);
}

void processData(int threadNumber, Barrier* barrier) {
	doWork(threadNumber);
	printf("Thread number %d waiting.\n", threadNumber);
	barrier->wait();
	doWork(THREADS-threadNumber/(currentTest+1));
	printf("Thread number %d finished working.\n", threadNumber);
}

void processDataWithTimeout(int threadNumber, Barrier* barrier, int MsToTimeout) {
	doWork(threadNumber);
	printf("Thread number %d waiting.\n", threadNumber);
	barrier->waitUntil(MsToTimeout);
	doWork(THREADS-threadNumber/(currentTest+1));
	printf("Thread number %d finished working.\n", threadNumber);
}

void waitForSignalTest() {
	printf("WaitForSignalTest.\n");
	Barrier barrier;

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i] = std::thread(processData, i, &barrier);
	}

	doWork(20);
	barrier.signal();

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i].join();
	}
}

void waitForNumberOfThreadsTest() {
	printf("WaitForNumberOfThreadsTest\n");
	Barrier barrier(THREADS);

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i] = std::thread(processData, i, &barrier);
	}

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i].join();
	}
}

void waitForTimeoutTest() {
	printf("WaitForTimeoutTest\n");
	Barrier barrier;

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i] = std::thread(processDataWithTimeout, i, &barrier, 5000);
	}

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i].join();
	}
}

void waitForSignalBeforeTimeoutTest() {
	printf("WaitForSignalBeforeTimeoutTest\n");
	Barrier barrier;

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i] = std::thread(processDataWithTimeout, i, &barrier, 5000);
	}

	doWork(100);
	barrier.signal();

	for (int i = currentTest*THREADS; i < (currentTest * THREADS) + THREADS; i++) {
		threadPool[i].join();
	}
}

int main (int argc, char* argv[]) {
	waitForSignalTest();
	printf("\n\n");
	currentTest++;
	waitForNumberOfThreadsTest();
	printf("\n\n");
	currentTest++;
	waitForTimeoutTest();
	printf("\n\n");
	currentTest++;
	waitForSignalBeforeTimeoutTest();

	return 0;
}