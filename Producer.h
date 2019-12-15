//
// Created by hadasswittow on 12/15/19.
//

#ifndef PRODUCERCONSUMERCPP_PRODUCER_H
#define PRODUCERCONSUMERCPP_PRODUCER_H

#include "WaitQueue.h"
#include <iostream>
#include <glob.h>
#include <pthread.h>
#include <cstdio>

#define PRODUCER_PRODUCTS 40
class Producer {
public:
    Producer(size_t id,WaitQueue<int>* queue):m_id(id),m_queue(queue){ pthread_mutex_init(&rand_mutex, NULL);}
    ~Producer(){ pthread_mutex_destroy(&rand_mutex);}
    void startProducing();
    void stopProducing();

private:
    static void* produce(void* param);
    size_t m_id;
    pthread_t thread;
    pthread_mutex_t rand_mutex;
    WaitQueue<int>* m_queue;

};
inline void Producer::startProducing() {
    pthread_create(&thread, NULL, produce, this);
}
inline void Producer::stopProducing(){
    void* ret_val;
    pthread_join(thread, &ret_val);
}
inline void* Producer::produce(void* param){
    Producer* _this = (Producer*)param;
    unsigned int random ;
    unsigned int counter = 0;
    while(counter < PRODUCER_PRODUCTS){
        pthread_mutex_lock(&_this->rand_mutex);
        random = rand() % 1000000 ;
        pthread_mutex_unlock(&_this->rand_mutex);
        _this->m_queue->pushItem(random);
        printf("Producer: %lu, iteration %d produced product number %d\n" ,_this->m_id,counter ,random);
        ++counter;
    }
}

#endif //PRODUCERCONSUMERCPP_PRODUCER_H
