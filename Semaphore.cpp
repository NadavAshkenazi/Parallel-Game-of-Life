#include "Semaphore.hpp"

Semaphore::Semaphore() : counter(0) {
    pthread_cond_init(&c, NULL);
    pthread_mutex_init(&m,NULL);
}
Semaphore::Semaphore(unsigned val) : counter(val) {
    pthread_cond_init(&c, NULL);
    pthread_mutex_init(&m,NULL);
}
Semaphore::~Semaphore() {
    pthread_cond_destroy (&c);
    pthread_mutex_destroy(&m);
}

void Semaphore::up() {
    pthread_mutex_lock(&m);
    counter++;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void Semaphore::down() {
    pthread_mutex_lock(&m);
    while (counter <= 0) {
        pthread_cond_wait(&c, &m);
    }
    counter--;
    pthread_mutex_unlock(&m);
}
