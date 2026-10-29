// Experiment 36: Linked file allocation
// Each file is a linked list of disk blocks that may be scattered anywhere on the disk.
// The directory stores pointers to the first and last block; each block points to the next one.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int DISK_BLOCKS = 20;
int nextBlock[DISK_BLOCKS];       // pointer stored in each block (-1 = end of file)
bool used[DISK_BLOCKS];

struct File { string name; int first, last, length; };
vector<File> directory;

void create(const string &name, int length, vector<int> preferred) {
    int prev = -1, first = -1, last = -1, count = 0;
    for (int b : preferred) {
        if (count == length) break;
        if (b < 0 || b >= DISK_BLOCKS || used[b]) continue;
        used[b] = true; nextBlock[b] = -1;
        if (prev != -1) nextBlock[prev] = b; else first = b;
        prev = b; last = b; count++;
    }
    if (count < length) { cout << "Not enough free blocks for '" << name << "'\n"; return; }
    directory.push_back({name, first, last, length});
    cout << "File '" << name << "' created: first block = " << first << ", last block = " << last << "\n";
}

void display() {
    cout << "\nDirectory:\nFile        First   Last   Length\n";
    for (auto &f : directory)
        cout << f.name << string(12 - f.name.size(), ' ') << f.first << "       " << f.last << "      " << f.length << "\n";

    cout << "\nBlock chains:\n";
    for (auto &f : directory) {
        cout << "  " << f.name << ": ";
        for (int b = f.first; b != -1; b = nextBlock[b]) cout << "[" << b << "]" << (nextBlock[b] != -1 ? " -> " : " -> NULL");
        cout << "\n";
    }
}

void read(const string &name, int k) {
    for (auto &f : directory)
        if (f.name == name) {
            cout << "Reading block #" << k << " of '" << name << "' by following pointers: ";
            int b = f.first;
            for (int i = 1; i < k && b != -1; i++) { cout << b << " -> "; b = nextBlock[b]; }
            cout << b << "\n";
            return;
        }
    cout << "File not found\n";
}

int main() {
    for (int i = 0; i < DISK_BLOCKS; i++) { used[i] = false; nextBlock[i] = -1; }

    cout << "--- Linked File Allocation (20-block disk) ---\n\n";
    create("fileA", 4, {9, 16, 1, 10, 25});          // scattered blocks
    create("fileB", 5, {2, 5, 7, 12, 18, 3});
    create("fileC", 3, {0, 4, 6});
    create("fileD", 2, {9, 1, 8, 13});               // 9 and 1 are used, so 8 and 13 are taken
    display();
    cout << "\n";
    read("fileB", 4);
    read("fileA", 3);
    return 0;
}
