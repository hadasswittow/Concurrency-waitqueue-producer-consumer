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
    Consumer(size_t id,WaitQueue<int>* queue):m_id(id),m_queue(queue),m_counter(0){};
    void startConsuming();
    void stopConsuming();

private:
    static void* consume(void* param);
    size_t m_id;
    pthread_t thread;
    unsigned int m_counter;
    WaitQueue<int> *m_queue;

};
inline void Consumer::startConsuming() {
    pthread_create(&thread, NULL, consume, this);
}
inline void Consumer::stopConsuming(){
    void* ret_val;
    m_counter = CONSUMER_PRODUCTS;
    pthread_join(thread, &ret_val);
}
inline void* Consumer::consume(void* param){
    Consumer* _this = (Consumer*)param;
    _this->m_counter = 0;
    int val;
    while(_this->m_counter < CONSUMER_PRODUCTS){
        val = _this->m_queue->front();
        if(_this->m_queue->tryPop())
        {
            printf("Consumer: %lu, iteration %d bought product number %d\n" ,_this->m_id,_this->m_counter ,val);
            ++_this->m_counter;
        }
        else
            sleep(0);
    }
}



#endif //PRODUCERCONSUMERCPP_CONSUMER_H
