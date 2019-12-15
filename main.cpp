#include <iostream>
#include <cstdlib>
#include "WaitQueue.h"
#include "Producer.h"
#include "Consumer.h"

#define QUEUE_SIZE 6
#define PRODUCERS_AMOUNT 3
#define CONSUMERS_AMOUNT 4

void createProducersAndConsumers(Producer *producers[], Consumer *consumers[], WaitQueue<int> &waitQueue);

void joinProducersAndConsumers(Producer *producers[], Consumer *consumers[]);

void testWaitQueue();

int main() {

    testWaitQueue(); // test the waiting queue wuth the producer consumer problem.

    return 0;
}

void testWaitQueue() {

    srand(time(0));
    
    Producer *producers[PRODUCERS_AMOUNT];
    Consumer *consumers[CONSUMERS_AMOUNT];
    WaitQueue<int> waitQueue(QUEUE_SIZE);

    createProducersAndConsumers(producers, consumers, waitQueue);
    joinProducersAndConsumers(producers, consumers);


}

void createProducersAndConsumers(Producer *producers[], Consumer *consumers[], WaitQueue<int> &waitQueue) {
    int i;
    for (i = 0; i < PRODUCERS_AMOUNT; ++i) {
        producers[i] = new Producer(i, &waitQueue);
        producers[i]->startProducing();
    }
    for (i = 0; i < CONSUMERS_AMOUNT; ++i) {
        consumers[i] = new Consumer(i, &waitQueue);
        consumers[i]->startConsuming();
    }
}

void joinProducersAndConsumers(Producer *producers[], Consumer *consumers[]) {
    int i;
    for (i = 0; i < PRODUCERS_AMOUNT; ++i) {
        producers[i]->stopProducing();
        delete (producers[i]);
    }
    for (i = 0; i < CONSUMERS_AMOUNT; ++i) {
        consumers[i]->stopConsuming();
        delete (consumers[i]);
    }
}