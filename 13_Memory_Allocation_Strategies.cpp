// Experiment 13: Memory allocation strategies - First Fit, Best Fit, Worst Fit
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

enum Strategy { FIRST, BEST, WORST };

void allocate(Strategy s, vector<int> block, const vector<int> &proc, const string &name) {
    cout << "\n===== " << name << " =====\n";
    cout << left << setw(10) << "Process" << setw(10) << "Size" << "Block allotted\n";
    int total = 0;
    for (size_t i = 0; i < proc.size(); i++) {
        int idx = -1;
        for (size_t j = 0; j < block.size(); j++) {
            if (block[j] < proc[i]) continue;
            if (s == FIRST) { idx = j; break; }
            if (idx == -1 || (s == BEST && block[j] < block[idx]) || (s == WORST && block[j] > block[idx])) idx = j;
        }
        cout << "P" << setw(9) << i + 1 << setw(10) << proc[i];
        if (idx != -1) { cout << "Block " << idx + 1 << endl; block[idx] -= proc[i]; }
        else cout << "Not allocated" << endl;
    }
    cout << "Remaining block sizes: ";
    for (int b : block) { cout << b << " "; total += b; }
    cout << "\nTotal free memory left: " << total << endl;
}

int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> procs  = {212, 417, 112, 426};

    cout << "Memory blocks : "; for (int b : blocks) cout << b << " ";
    cout << "\nProcess sizes : "; for (int p : procs) cout << p << " ";
    cout << endl;

    allocate(FIRST, blocks, procs, "FIRST FIT");
    allocate(BEST,  blocks, procs, "BEST FIT");
    allocate(WORST, blocks, procs, "WORST FIT");
    return 0;
}
