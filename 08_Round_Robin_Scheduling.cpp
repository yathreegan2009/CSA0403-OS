// Experiment 8: Round Robin CPU Scheduling
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

int main() {
    int n = 5, quantum = 3;
    int at[] = {0, 1, 2, 3, 4};
    int bt[] = {5, 4, 2, 1, 6};
    int rem[5], ct[5], wt[5], tat[5];
    for (int i = 0; i < n; i++) rem[i] = bt[i];

    queue<int> q;
    bool inQueue[5] = {false};
    int time = 0, done = 0;
    q.push(0); inQueue[0] = true;

    cout << "Round Robin Scheduling (Time Quantum = " << quantum << ")\n\nGantt Chart:\n";
    while (done < n) {
        if (q.empty()) {                      // CPU idle, jump to next arrival
            for (int i = 0; i < n; i++)
                if (rem[i] > 0 && !inQueue[i]) { time = max(time, at[i]); q.push(i); inQueue[i] = true; break; }
        }
        int i = q.front(); q.pop();
        int run = min(quantum, rem[i]);
        cout << "| P" << i + 1 << " (" << time << "-" << time + run << ") ";
        time += run;
        rem[i] -= run;

        for (int j = 0; j < n; j++)           // add newly arrived processes
            if (!inQueue[j] && at[j] <= time && rem[j] > 0) { q.push(j); inQueue[j] = true; }

        if (rem[i] > 0) q.push(i);
        else { ct[i] = time; done++; }
    }
    cout << "|\n";

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
