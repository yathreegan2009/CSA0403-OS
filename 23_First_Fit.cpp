// Experiment 23: First Fit memory allocation
// Each process is placed in the FIRST block that is big enough.
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    vector<int> block = {100, 500, 200, 300, 600};
    vector<int> proc  = {212, 417, 112, 426};
    vector<int> original = block;

    cout << "First Fit Memory Allocation\n\n";
    cout << left << setw(10) << "Process" << setw(12) << "Size" << setw(10) << "Block" << "Block size (before)\n";

    for (size_t i = 0; i < proc.size(); i++) {
        int found = -1;
        for (size_t j = 0; j < block.size(); j++)
            if (block[j] >= proc[i]) { found = j; break; }

        cout << "P" << setw(9) << i + 1 << setw(12) << proc[i];
        if (found != -1) {
            cout << setw(10) << found + 1 << block[found] << endl;
            block[found] -= proc[i];
        } else cout << "Not allocated (no block large enough)" << endl;
    }

    cout << "\nBlock    Original    Remaining\n";
    for (size_t j = 0; j < block.size(); j++)
        cout << j + 1 << "        " << setw(12) << left << original[j] << block[j] << endl;
    return 0;
}
