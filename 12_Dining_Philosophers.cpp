// Experiment 12: Dining Philosophers problem
// Deadlock is avoided by making the last philosopher pick the forks in reverse order.
// Compile: g++ 12_Dining_Philosophers.cpp -o 12 -pthread
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

const int N = 5;
mutex fork_[N];
mutex printLock;

void say(int id, const string &s) {
    lock_guard<mutex> g(printLock);
    cout << "Philosopher " << id << " " << s << endl;
}

void philosopher(int id) {
    int left = id, right = (id + 1) % N;
    if (id == N - 1) swap(left, right);         // break circular wait

    for (int round = 1; round <= 2; round++) {
        say(id, "is THINKING");
        this_thread::sleep_for(chrono::milliseconds(200 + id * 50));

        say(id, "is HUNGRY");
        fork_[left].lock();
        fork_[right].lock();

        say(id, "is EATING (has forks " + to_string(id) + " and " + to_string((id + 1) % N) + ")");
        this_thread::sleep_for(chrono::milliseconds(300));

        fork_[right].unlock();
        fork_[left].unlock();
        say(id, "finished eating and put down the forks");
    }
}

int main() {
    cout << "Dining Philosophers Simulation (5 philosophers, 2 meals each)\n\n";
    thread t[N];
    for (int i = 0; i < N; i++) t[i] = thread(philosopher, i);
    for (int i = 0; i < N; i++) t[i].join();
    cout << "\nAll philosophers have finished eating. No deadlock occurred." << endl;
    return 0;
}
