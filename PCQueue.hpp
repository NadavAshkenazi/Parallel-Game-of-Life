#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"
#include "Semaphore.hpp"

using namespace std;

// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:
    PCQueue(){
        s = new Semaphore(0);
    };
    // Blocks while queue is empty. When queue holds items, allows for a single
    // thread to enter and remove an item from the front of the queue and return it.
    // Assumes multiple consumers.
    T pop(){
        s->down();
        pthread_mutex_lock(&global_lock);
        T item = queue.pop();
        pthread_mutex_unlock(&global_lock);
        return item;
    };

    // Allows for producer to enter with *minimal delay* and push items to back of the queue.
    // Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.
    // Assumes single producer
    void push(const T& item){
        pthread_mutex_lock(&global_lock);
        queue.push(item);
        s->up();
        pthread_mutex_unlock(&global_lock);
    };


private:
    // Add your class members here
//    pthread_cond_t read_allowed;
//    pthread_cond_t write_allowed;
    pthread_mutex_t global_lock;
    queue<T> queue;
    Semaphore* s;
};
// Recommendation: Use the implementation of the std::queue for this exercise


#endif