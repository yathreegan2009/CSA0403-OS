// Experiment 20: Reader-Writer problem using semaphores (readers preference)
// Compile: g++ 20_Reader_Writer_Semaphores.cpp -o 20 -pthread
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t wrt, mutex_, print_;
int readCount = 0;
int sharedData = 0;

void *reader(void *arg) {
    int id = *(int *)arg;
    sem_wait(&mutex_);
    readCount++;
    if (readCount == 1) sem_wait(&wrt);        // first reader blocks writers
    sem_post(&mutex_);

    sem_wait(&print_);
    cout << "Reader " << id << " reads data = " << sharedData << "   (readers inside: " << readCount << ")" << endl;
    sem_post(&print_);
    usleep(200000);

    sem_wait(&mutex_);
    readCount--;
    if (readCount == 0) sem_post(&wrt);        // last reader lets writers in
    sem_post(&mutex_);
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    sem_wait(&wrt);                            // exclusive access
    sharedData++;
    sem_wait(&print_);
    cout << "Writer " << id << " wrote data = " << sharedData << endl;
    sem_post(&print_);
    usleep(300000);
    sem_post(&wrt);
    return NULL;
}

int main() {
    sem_init(&wrt, 0, 1); sem_init(&mutex_, 0, 1); sem_init(&print_, 0, 1);

    pthread_t r[4], w[2];
    int rid[4] = {1, 2, 3, 4}, wid[2] = {1, 2};

    pthread_create(&r[0], NULL, reader, &rid[0]);
    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&r[1], NULL, reader, &rid[1]);
    pthread_create(&r[2], NULL, reader, &rid[2]);
    pthread_create(&w[1], NULL, writer, &wid[1]);
    pthread_create(&r[3], NULL, reader, &rid[3]);

    for (int i = 0; i < 4; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);

    cout << "\nFinal value of shared data = " << sharedData << endl;
    return 0;
}
