// Experiment 18: Producer-Consumer problem using semaphores
// Compile: g++ 18_Producer_Consumer_Semaphores.cpp -o 18 -pthread
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

const int BUFFER_SIZE = 5, ITEMS = 10;
int buffer[BUFFER_SIZE], in = 0, out = 0;

sem_t empty_, full_, mutex_;

void *producer(void *) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty_);             // wait for an empty slot
        sem_wait(&mutex_);             // enter critical section
        buffer[in] = i;
        cout << "Producer produced item " << i << " at position " << in << endl;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex_);
        sem_post(&full_);              // signal one more full slot
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full_);              // wait for a full slot
        sem_wait(&mutex_);
        int item = buffer[out];
        cout << "                         Consumer consumed item " << item << " from position " << out << endl;
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex_);
        sem_post(&empty_);             // signal one more empty slot
        usleep(250000);
    }
    return NULL;
}

int main() {
    sem_init(&empty_, 0, BUFFER_SIZE);
    sem_init(&full_, 0, 0);
    sem_init(&mutex_, 0, 1);

    pthread_t p, c;
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty_); sem_destroy(&full_); sem_destroy(&mutex_);
    cout << "\nAll items produced and consumed successfully." << endl;
    return 0;
}
