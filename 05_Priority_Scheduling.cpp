// Experiment 5: Scheduling that selects the waiting process with the HIGHEST priority
// (Non-preemptive priority scheduling; lower number = higher priority; arrival = 0)
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process { int id, burst, priority, wt, tat; };

int main() {
    Process p[] = {{1, 10, 3}, {2, 1, 1}, {3, 2, 4}, {4, 1, 5}, {5, 5, 2}};
    int n = 5;

    sort(p, p + n, [](const Process &a, const Process &b) { return a.priority < b.priority; });

    int time = 0;
    double tw = 0, tt = 0;
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].burst;
        p[i].tat = time;
        tw += p[i].wt; tt += p[i].tat;
    }

    cout << "Priority Scheduling (lower number = higher priority)\n\n";
    cout << left << setw(10) << "Process" << setw(10) << "Burst" << setw(10) << "Priority"
         << setw(10) << "Waiting" << "Turnaround\n";
    for (int i = 0; i < n; i++)
        cout << "P" << setw(9) << p[i].id << setw(10) << p[i].burst << setw(10) << p[i].priority
             << setw(10) << p[i].wt << p[i].tat << endl;

    cout << fixed << setprecision(2);
    cout << "\nExecution order : ";
    for (int i = 0; i < n; i++) cout << "P" << p[i].id << (i < n - 1 ? " -> " : "\n");
    cout << "Average Waiting Time    : " << tw / n << endl;
    cout << "Average Turnaround Time : " << tt / n << endl;
    return 0;
}
