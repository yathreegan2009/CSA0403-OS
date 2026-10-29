// Experiment 29: Classical process synchronization problem - SLEEPING BARBER
// One barber, 3 waiting chairs. If no customer, barber sleeps. If chairs are full, customer leaves.
// Compile: g++ 29_Sleeping_Barber_Problem.cpp -o 29 -pthread
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

const int CHAIRS = 3, CUSTOMERS = 8;
sem_t customers, barber, mutex_, print_;
int waiting = 0, served = 0, left_ = 0;

void say(const string &s) { sem_wait(&print_); cout << s << endl; sem_post(&print_); }

void *barberThread(void *) {
    while (true) {
        sem_wait(&mutex_);
        bool noOne = (waiting == 0);
        sem_post(&mutex_);
        if (noOne) say("Barber is sleeping (waiting for a customer)...");
        sem_wait(&customers);                 // sleep until a customer arrives
        sem_wait(&mutex_);
        waiting--;
        sem_post(&barber);                    // call next customer
        sem_post(&mutex_);
        say("Barber is cutting hair");
        usleep(500000);
        say("Barber finished a haircut");
        served++;
        if (served + left_ == CUSTOMERS) break;
    }
    return NULL;
}

void *customerThread(void *arg) {
    int id = *(int *)arg;
    sem_wait(&mutex_);
    if (waiting < CHAIRS) {
        waiting++;
        say("Customer " + to_string(id) + " sits in waiting room (waiting = " + to_string(waiting) + ")");
        sem_post(&customers);                 // wake barber
        sem_post(&mutex_);
        sem_wait(&barber);                    // wait for barber
        say("Customer " + to_string(id) + " is getting a haircut");
    } else {
        left_++;
        say("Customer " + to_string(id) + " finds no free chair and LEAVES");
        sem_post(&mutex_);
    }
    return NULL;
}

int main() {
    sem_init(&customers, 0, 0); sem_init(&barber, 0, 0);
    sem_init(&mutex_, 0, 1);    sem_init(&print_, 0, 1);

    pthread_t b, c[CUSTOMERS];
    int id[CUSTOMERS];
    pthread_create(&b, NULL, barberThread, NULL);
    for (int i = 0; i < CUSTOMERS; i++) {
        id[i] = i + 1;
        pthread_create(&c[i], NULL, customerThread, &id[i]);
        usleep(150000);
    }
    for (int i = 0; i < CUSTOMERS; i++) pthread_join(c[i], NULL);
    pthread_join(b, NULL);

    cout << "\nCustomers served: " << served << ", customers who left: " << left_ << endl;
    return 0;
}
