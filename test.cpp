#include "Semaphore.hpp"
#include <iostream>
#include "PCQueue.hpp"

Semaphore* s = new Semaphore(1);
Semaphore* s2 = new Semaphore(2);
Semaphore* s0 = new Semaphore();
PCQueue<int>* queue1 = new PCQueue<int>();

void* sleep_test(void* ptr){
    s->down();
    sleep(10);
    string* name = new string((char*)ptr);
    cout << *name << endl;
    s->up();
    return NULL;
}

void* sleep_test2(void* ptr){
    s2->down();
    sleep(5);
    string* name = new string((char*)ptr);
    cout << *name << endl;
    s2->up();
    return NULL;
}

void* sleep_test0(void* ptr){
    s0->up();
    sleep(5);
    string* name = new string((char*)ptr);
    cout << *name << endl;
    s0->down();
    return NULL;
}


void* pop(void* harta) {
    cout << "poped: " << queue1->pop() << endl ;
    return NULL;
}

void* push(void* val){
    int val_int = *((int*)val);
    queue1->push(val_int);
    cout << "pushed: "<< val_int << endl ;
    return NULL;
}


int main() {

// semaphore test
/*
    pthread_t t1;
    const char* n1 = "I'm Thread 1!";
    const char* n2 = "I'm Thread 2!";
    pthread_create(&t1, NULL, sleep_test, (void*)n2);
    sleep_test((void*)n1);
    pthread_join(t1, NULL);

    pthread_t t3;
    pthread_t t4;
    pthread_t t5;
    const char* n3 = "I'm Thread 3!";
    const char* n4 = "I'm Thread 4!";
    const char* n5 = "I'm Thread 5!";
    pthread_create(&t3, NULL, sleep_test2, (void*)n3);
    pthread_create(&t4, NULL, sleep_test2, (void*)n4);
    pthread_create(&t5, NULL, sleep_test2, (void*)n5);
    //sleep_test((void*)n1);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
*/

    pthread_t t3;
    pthread_t t4;
    pthread_t t5;
    pthread_t t6;

    int n = 5;
    int* num = &n;
    int n1 = 6;
    int* num1 = &n1;
    pthread_create(&t3, NULL, pop, (void*)num);
    pthread_create(&t4, NULL, push, (void*)num);
    pthread_create(&t5, NULL, pop,(void*)num);
    pthread_create(&t6, NULL, push, (void*)num1);

    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);

    return 0;
}
