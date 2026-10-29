// Experiment 11: Multithreading using C++ threads
// Compile: g++ 11_Multithreading.cpp -o 11 -pthread
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex printLock;

void task(int id) {
    for (int i = 1; i <= 3; i++) {
        {
            lock_guard<mutex> g(printLock);
            cout << "Thread " << id << " is running (step " << i << ")" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void sumArray(const vector<int> &v, int from, int to, long &result) {
    result = 0;
    for (int i = from; i < to; i++) result += v[i];
}

int main() {
    cout << "--- Part 1: Running 3 threads concurrently ---\n";
    thread t1(task, 1), t2(task, 2), t3(task, 3);
    t1.join(); t2.join(); t3.join();

    cout << "\n--- Part 2: Sum of 1..1000 using 2 threads ---\n";
    vector<int> v(1000);
    for (int i = 0; i < 1000; i++) v[i] = i + 1;
    long s1, s2;
    thread a(sumArray, cref(v), 0, 500, ref(s1));
    thread b(sumArray, cref(v), 500, 1000, ref(s2));
    a.join(); b.join();
    cout << "Thread A sum (1..500)    = " << s1 << endl;
    cout << "Thread B sum (501..1000) = " << s2 << endl;
    cout << "Total                    = " << s1 + s2 << endl;
    return 0;
}
