// Experiment 4: Scheduling that selects the waiting process with the SMALLEST execution time
// (Shortest Job First, all processes available at time 0)
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process { int id, burst, wt, tat; };

int main() {
    Process p[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}, {5, 4}};
    int n = 5;

    // pick the process with smallest burst time first
    sort(p, p + n, [](const Process &a, const Process &b) { return a.burst < b.burst; });

    int time = 0;
    double tw = 0, tt = 0;
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].burst;
        p[i].tat = time;
        tw += p[i].wt; tt += p[i].tat;
    }

    cout << "Shortest Execution Time First Scheduling\n\n";
    cout << left << setw(10) << "Process" << setw(10) << "Burst" << setw(10) << "Waiting" << "Turnaround\n";
    for (int i = 0; i < n; i++)
        cout << "P" << setw(9) << p[i].id << setw(10) << p[i].burst << setw(10) << p[i].wt << p[i].tat << endl;

    cout << fixed << setprecision(2);
    cout << "\nExecution order : ";
    for (int i = 0; i < n; i++) cout << "P" << p[i].id << (i < n - 1 ? " -> " : "\n");
    cout << "Average Waiting Time    : " << tw / n << endl;
    cout << "Average Turnaround Time : " << tt / n << endl;
    return 0;
}
