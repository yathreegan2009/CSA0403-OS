// Experiment 7: Non-preemptive Shortest Job First (with arrival times)
#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int main() {
    int n = 5;
    int at[] = {0, 2, 4, 5, 6};       // arrival times
    int bt[] = {7, 4, 1, 4, 2};       // burst times
    int ct[5], wt[5], tat[5];
    bool finished[5] = {false};

    int time = 0, done = 0;
    cout << "Non-Preemptive SJF Scheduling\n\nExecution order: ";
    while (done < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!finished[i] && at[i] <= time && bt[i] < best) { best = bt[i]; idx = i; }

        if (idx == -1) { time++; continue; }          // CPU idle
        time += bt[idx];
        ct[idx] = time;
        finished[idx] = true;
        done++;
        cout << "P" << idx + 1 << (done < n ? " -> " : "\n");
    }

    double tw = 0, tt = 0;
    cout << "\n" << left << setw(9) << "Process" << setw(9) << "Arrival" << setw(8) << "Burst"
         << setw(12) << "Completion" << setw(12) << "Turnaround" << "Waiting\n";
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        tw += wt[i]; tt += tat[i];
        cout << "P" << setw(8) << i + 1 << setw(9) << at[i] << setw(8) << bt[i]
             << setw(12) << ct[i] << setw(12) << tat[i] << wt[i] << endl;
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time    : " << tw / n << endl;
    cout << "Average Turnaround Time : " << tt / n << endl;
    return 0;
}
