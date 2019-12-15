//
// Created by hadasswittow on 12/15/19.
//

#ifndef PRODUCERCONSUMERCPP_WAITQUEUE_H
#define PRODUCERCONSUMERCPP_WAITQUEUE_H
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
using std::queue;

template<typename T>
class WaitQueue {
public:
    WaitQueue(size_t size);
    ~WaitQueue();
    size_t size(){ return m_size;}
    void pushItem(T item);
    T popItem();
private:
    size_t m_size;
    queue<T> waiting_queue;
    pthread_mutex_t mutex;
    sem_t sem_empty;
    sem_t sem_full;
};

template<typename T>
inline WaitQueue<T>::WaitQueue(size_t size):m_size(size){
    sem_init(&sem_empty, 0, size);
    sem_init(&sem_full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
}
template<typename T>
inline WaitQueue<T>::~WaitQueue() {
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
}
template<typename T>
inline void WaitQueue<T>::pushItem(T item){
    sem_wait(&sem_empty);
    pthread_mutex_lock(&mutex);
    waiting_queue.push(item);
    pthread_mutex_unlock(&mutex);
    sem_post(&sem_full);
}
template<typename T>
inline T WaitQueue<T>::popItem() {
    T item;
    sem_wait(&sem_full);
    pthread_mutex_lock(&mutex);
    item = waiting_queue.front();
    waiting_queue.pop();
    pthread_mutex_unlock(&mutex);
    sem_post(&sem_empty);
    return item;
}

#endif //PRODUCERCONSUMERCPP_WAITQUEUE_H
