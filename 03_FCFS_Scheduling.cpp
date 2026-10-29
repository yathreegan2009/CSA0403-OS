// Experiment 3: First Come First Served (FCFS) CPU scheduling
// All processes arrive at time 0, no process waits for I/O
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
    int n = 5;
    int burst[] = {10, 5, 8, 6, 3};          // sample burst times

    vector<int> wt(n), tat(n);
    wt[0] = 0;
    for (int i = 1; i < n; i++) wt[i] = wt[i - 1] + burst[i - 1];
    for (int i = 0; i < n; i++) tat[i] = wt[i] + burst[i];

    cout << "FCFS CPU Scheduling (arrival time = 0 for all)\n\n";
    cout << left << setw(10) << "Process" << setw(12) << "Burst" << setw(12) << "Waiting" << "Turnaround\n";
    double tw = 0, tt = 0;
    for (int i = 0; i < n; i++) {
        cout << left << "P" << setw(9) << i + 1 << setw(12) << burst[i] << setw(12) << wt[i] << tat[i] << endl;
        tw += wt[i]; tt += tat[i];
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time    : " << tw / n << endl;
    cout << "Average Turnaround Time : " << tt / n << endl;

    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++) cout << " P" << i + 1 << " |";
    cout << "\n0";
    int t = 0;
    for (int i = 0; i < n; i++) { t += burst[i]; cout << setw(5) << t; }
    cout << endl;
    return 0;
}
