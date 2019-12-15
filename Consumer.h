//
// Created by hadasswittow on 12/15/19.
//

#ifndef PRODUCERCONSUMERCPP_CONSUMER_H
#define PRODUCERCONSUMERCPP_CONSUMER_H

#include "WaitQueue.h"
#include <glob.h>
#include <pthread.h>
#include <cstdio>

#define CONSUMER_PRODUCTS 30

class Consumer {
public:
    Consumer(size_t id,WaitQueue* queue):m_id(id),m_queue(queue){};
    void startConsuming();
    void stopConsuming();

private:
    static void* consume(void* param);
    size_t m_id;
    pthread_t thread;
    WaitQueue *m_queue;

};
inline void Consumer::startConsuming() {
    pthread_create(&thread, NULL, consume, this);
}
inline void Consumer::stopConsuming(){
    void* ret_val;
    pthread_join(thread, &ret_val);
}
inline void* Consumer::consume(void* param){
    Consumer* _this = (Consumer*)param;
    unsigned int counter = 0;
    int val;
    while(counter < CONSUMER_PRODUCTS){
        val = _this->m_queue->popItem();
        printf("Consumer: %lu, iteration %d bought product number %d\n" ,_this->m_id,counter ,val);
        ++counter;
    }
}



#endif //PRODUCERCONSUMERCPP_CONSUMER_H
