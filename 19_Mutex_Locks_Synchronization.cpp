// Experiment 19: Process (thread) synchronization using mutex locks
// Shows a race condition WITHOUT the mutex and the correct result WITH it.
// Compile: g++ 19_Mutex_Locks_Synchronization.cpp -o 19 -pthread
#include <iostream>
#include <pthread.h>
using namespace std;

const int THREADS = 4, INCREMENTS = 200000;
volatile long unsafeCounter = 0;
long safeCounter = 0;
pthread_mutex_t lock_ = PTHREAD_MUTEX_INITIALIZER;

void *unsafeWork(void *) {
    for (int i = 0; i < INCREMENTS; i++) unsafeCounter = unsafeCounter + 1;   // no protection
    return NULL;
}

void *safeWork(void *) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock_);        // enter critical section
        safeCounter++;
        pthread_mutex_unlock(&lock_);      // leave critical section
    }
    return NULL;
}

int main() {
    pthread_t t[THREADS];
    cout << "Each of " << THREADS << " threads increments the counter " << INCREMENTS << " times.\n";
    cout << "Expected final value = " << (long)THREADS * INCREMENTS << "\n\n";

    for (int i = 0; i < THREADS; i++) pthread_create(&t[i], NULL, unsafeWork, NULL);
    for (int i = 0; i < THREADS; i++) pthread_join(t[i], NULL);
    cout << "Without mutex : " << unsafeCounter << "   (no lock: race condition, result may be WRONG)\n";

    for (int i = 0; i < THREADS; i++) pthread_create(&t[i], NULL, safeWork, NULL);
    for (int i = 0; i < THREADS; i++) pthread_join(t[i], NULL);
    cout << "With mutex    : " << safeCounter << "   (always CORRECT)\n";

    pthread_mutex_destroy(&lock_);
    return 0;
}
