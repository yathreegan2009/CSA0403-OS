// Experiment 21: Worst Fit memory allocation
// Each process is placed in the LARGEST block that can hold it.
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    vector<int> block = {100, 500, 200, 300, 600};
    vector<int> proc  = {212, 417, 112, 426};
    vector<int> original = block;

    cout << "Worst Fit Memory Allocation\n\n";
    cout << left << setw(10) << "Process" << setw(12) << "Size" << setw(10) << "Block" << "Block size (before)\n";

    for (size_t i = 0; i < proc.size(); i++) {
        int worst = -1;
        for (size_t j = 0; j < block.size(); j++)
            if (block[j] >= proc[i] && (worst == -1 || block[j] > block[worst])) worst = j;

        cout << "P" << setw(9) << i + 1 << setw(12) << proc[i];
        if (worst != -1) {
            cout << setw(10) << worst + 1 << block[worst] << endl;
            block[worst] -= proc[i];
        } else cout << "Not allocated (no block large enough)" << endl;
    }

    cout << "\nBlock    Original    Remaining\n";
    for (size_t j = 0; j < block.size(); j++)
        cout << j + 1 << "        " << setw(12) << left << original[j] << block[j] << endl;
    return 0;
}
