// Experiment 17: Deadlock avoidance using Banker's Algorithm
// (Safety algorithm + Resource-Request algorithm)
#include <iostream>
#include <vector>
using namespace std;

const int P = 5, R = 3;
int alloc[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int maxm [P][R] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
int avail[R]    = {3,3,2};
int need[P][R];

// Safety algorithm: returns true and fills seq if the state is safe
bool isSafe(vector<int> &seq) {
    int work[R]; for (int j = 0; j < R; j++) work[j] = avail[j];
    bool finish[P] = {false};
    seq.clear();
    while ((int)seq.size() < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (finish[i]) continue;
            bool ok = true;
            for (int j = 0; j < R; j++) if (need[i][j] > work[j]) { ok = false; break; }
            if (ok) {
                for (int j = 0; j < R; j++) work[j] += alloc[i][j];
                finish[i] = true; seq.push_back(i); found = true;
            }
        }
        if (!found) break;
    }
    return (int)seq.size() == P;
}

void printState() {
    cout << "Process  Allocation  Max      Need\n";
    for (int i = 0; i < P; i++) {
        cout << "P" << i << "       ";
        for (int j = 0; j < R; j++) cout << alloc[i][j] << " ";
        cout << "      ";
        for (int j = 0; j < R; j++) cout << maxm[i][j] << " ";
        cout << "    ";
        for (int j = 0; j < R; j++) cout << need[i][j] << " ";
        cout << endl;
    }
    cout << "\nAvailable: "; for (int j = 0; j < R; j++) cout << avail[j] << " "; cout << "\n\n";
}

void request(int pid, int req[R]) {
    cout << "P" << pid << " requests (" << req[0] << ", " << req[1] << ", " << req[2] << ")\n";
    for (int j = 0; j < R; j++)
        if (req[j] > need[pid][j]) { cout << "  -> DENIED: process has exceeded its maximum claim.\n\n"; return; }
    for (int j = 0; j < R; j++)
        if (req[j] > avail[j]) { cout << "  -> P" << pid << " must WAIT: resources not available.\n\n"; return; }

    // pretend to allocate
    for (int j = 0; j < R; j++) { avail[j] -= req[j]; alloc[pid][j] += req[j]; need[pid][j] -= req[j]; }
    vector<int> seq;
    if (isSafe(seq)) {
        cout << "  -> GRANTED. System stays SAFE. Safe sequence: ";
        for (size_t i = 0; i < seq.size(); i++) cout << "P" << seq[i] << (i + 1 < seq.size() ? " -> " : "\n\n");
    } else {
        // roll back
        for (int j = 0; j < R; j++) { avail[j] += req[j]; alloc[pid][j] -= req[j]; need[pid][j] += req[j]; }
        cout << "  -> DENIED: granting it would leave the system in an UNSAFE state.\n\n";
    }
}

int main() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++) need[i][j] = maxm[i][j] - alloc[i][j];

    printState();
    vector<int> seq;
    if (isSafe(seq)) {
        cout << "The system is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < P; i++) cout << "P" << seq[i] << (i < P - 1 ? " -> " : "\n\n");
    } else cout << "The system is NOT in a safe state (deadlock possible).\n\n";

    int r1[R] = {1, 0, 2};  request(1, r1);     // should be granted
    int r2[R] = {3, 3, 0};  request(4, r2);     // not enough available
    int r3[R] = {0, 2, 0};  request(0, r3);     // leads to unsafe state
    return 0;
}
