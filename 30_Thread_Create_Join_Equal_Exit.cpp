// Experiment 30: Thread concepts - (i) create (ii) join (iii) equal (iv) exit
// Compile: g++ 30_Thread_Create_Join_Equal_Exit.cpp -o 30 -pthread
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_t mainThread;

void *worker(void *arg) {
    int id = *(int *)arg;
    pthread_t self = pthread_self();

    cout << "[Thread " << id << "] started" << endl;
    // (iii) pthread_equal : compare thread IDs
    if (pthread_equal(self, mainThread)) cout << "[Thread " << id << "] I am the same as the main thread" << endl;
    else cout << "[Thread " << id << "] pthread_equal(): I am NOT the main thread" << endl;
    if (pthread_equal(self, pthread_self())) cout << "[Thread " << id << "] pthread_equal(): my own ID matches itself" << endl;

    sleep(1);
    // (iv) pthread_exit : terminate the thread and return a value
    int *result = new int(id * 100);
    cout << "[Thread " << id << "] calling pthread_exit() with value " << *result << endl;
    pthread_exit(result);
    return NULL;        // never reached
}

int main() {
    mainThread = pthread_self();
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // (i) pthread_create
    pthread_create(&t1, NULL, worker, &id1);
    pthread_create(&t2, NULL, worker, &id2);
    cout << "[Main] Created two threads using pthread_create()" << endl;
    cout << "[Main] pthread_equal(t1, t2) = " << (pthread_equal(t1, t2) ? "equal" : "not equal") << endl;
    cout << "[Main] pthread_equal(t1, t1) = " << (pthread_equal(t1, t1) ? "equal" : "not equal") << endl;

    // (ii) pthread_join : wait for threads and collect return value
    void *r1, *r2;
    pthread_join(t1, &r1);
    cout << "[Main] pthread_join(): thread 1 returned " << *(int *)r1 << endl;
    pthread_join(t2, &r2);
    cout << "[Main] pthread_join(): thread 2 returned " << *(int *)r2 << endl;

    delete (int *)r1; delete (int *)r2;
    cout << "[Main] All threads finished" << endl;
    return 0;
}
