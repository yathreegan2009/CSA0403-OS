// Experiment 6: Preemptive Priority Scheduling (lower number = higher priority)
#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int main() {
    int n = 5;
    int at[]  = {0, 1, 2, 3, 4};      // arrival times
    int bt[]  = {10, 5, 2, 4, 3};     // burst times
    int pr[]  = {3, 2, 4, 1, 5};      // priorities
    int rem[5], ct[5], wt[5], tat[5];
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    int done = 0, time = 0, last = -1;
    cout << "Preemptive Priority Scheduling\n\nGantt Chart (time : process)\n";
    while (done < n) {
        int idx = -1, best = INT_MAX;
        for (int i = 0; i < n; i++)
            if (at[i] <= time && rem[i] > 0 && pr[i] < best) { best = pr[i]; idx = i; }

        if (idx == -1) { time++; continue; }          // CPU idle
        if (idx != last) { cout << "t=" << time << " : P" << idx + 1 << endl; last = idx; }

        rem[idx]--;
        time++;
        if (rem[idx] == 0) { ct[idx] = time; done++; }
    }

    double tw = 0, tt = 0;
    cout << "\n" << left << setw(9) << "Process" << setw(9) << "Arrival" << setw(8) << "Burst"
         << setw(10) << "Priority" << setw(12) << "Completion" << setw(12) << "Turnaround" << "Waiting\n";
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        tw += wt[i]; tt += tat[i];
        cout << "P" << setw(8) << i + 1 << setw(9) << at[i] << setw(8) << bt[i] << setw(10) << pr[i]
             << setw(12) << ct[i] << setw(12) << tat[i] << wt[i] << endl;
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time    : " << tw / n << endl;
    cout << "Average Turnaround Time : " << tt / n << endl;
    return 0;
}
