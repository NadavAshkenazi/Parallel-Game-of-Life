#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"
#include "Semaphore.hpp"


// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:
    PCQueue(){
        s = new Semaphore(0);
        q = new std::queue<T>();
    };
    // Blocks while queue is empty. When queue holds items, allows for a single
    // thread to enter and remove an item from the front of the queue and return it.
    // Assumes multiple consumers.
    T pop(){
        s->down();
        pthread_mutex_lock(&global_lock);
        T item = q->front();
        q->pop();
        pthread_mutex_unlock(&global_lock);
        return item;
    };

    // Allows for producer to enter with *minimal delay* and push items to back of the queue.
    // Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.
    // Assumes single producer
    void push(const T& item){
        pthread_mutex_lock(&global_lock);
        q->push(item);
        s->up();
        pthread_mutex_unlock(&global_lock);
    };

    /*
    void print(){
        for (auto it = q->begin(); it != q->end() ; ++it){
            cout <<
        }
    }
    */


private:
    // Add your class members here
//    pthread_cond_t read_allowed;
//    pthread_cond_t write_allowed;
    pthread_mutex_t global_lock;
    std::queue<T>* q;
    Semaphore* s;
};
// Recommendation: Use the implementation of the std::queue for this exercise


#endif