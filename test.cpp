#include "Semaphore.hpp"
#include <iostream>

Semaphore* s = new Semaphore(1);
Semaphore* s2 = new Semaphore(2);
Semaphore* s0 = new Semaphore();

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


int main() {
   /*
    pthread_t t1;
    const char* n1 = "I'm Thread 1!";
    const char* n2 = "I'm Thread 2!";
    pthread_create(&t1, NULL, sleep_test, (void*)n2);
    sleep_test((void*)n1);
    pthread_join(t1, NULL);
*/
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


    return 0;
}
