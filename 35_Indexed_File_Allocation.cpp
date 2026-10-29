// Experiment 35: Indexed file allocation
// All block pointers of a file are kept together in one INDEX BLOCK.
// The i-th entry of the index block points to the i-th block of the file.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int DISK_BLOCKS = 30;
bool used[DISK_BLOCKS] = {false};

struct File { string name; int indexBlock; vector<int> blocks; };
vector<File> directory;

int freeBlock() {
    for (int i = 0; i < DISK_BLOCKS; i++) if (!used[i]) return i;
    return -1;
}

void create(const string &name, int nblocks) {
    int free = 0;
    for (int i = 0; i < DISK_BLOCKS; i++) if (!used[i]) free++;
    if (free < nblocks + 1) { cout << "Not enough free blocks for file '" << name << "'\n"; return; }

    File f; f.name = name;
    f.indexBlock = freeBlock(); used[f.indexBlock] = true;
    // scatter blocks (skip every other free block) to show they need not be contiguous
    int skip = 0;
    for (int i = 0; i < DISK_BLOCKS && (int)f.blocks.size() < nblocks; i++)
        if (!used[i]) { if (skip++ % 2 == 0 || free - skip < nblocks) { used[i] = true; f.blocks.push_back(i); } }
    for (int i = 0; i < DISK_BLOCKS && (int)f.blocks.size() < nblocks; i++)
        if (!used[i]) { used[i] = true; f.blocks.push_back(i); }
    directory.push_back(f);
    cout << "File '" << name << "' created with index block " << f.indexBlock << "\n";
}

void display() {
    for (auto &f : directory) {
        cout << "\nFile: " << f.name << "   Index block: " << f.indexBlock << "\n";
        cout << "  Index block contents:\n";
        for (size_t i = 0; i < f.blocks.size(); i++)
            cout << "    entry " << i << " -> disk block " << f.blocks[i] << "\n";
    }
}

void access(const string &name, int i) {
    for (auto &f : directory)
        if (f.name == name) {
            if (i < 0 || i >= (int)f.blocks.size()) { cout << "Invalid block number\n"; return; }
            cout << "Block " << i << " of '" << name << "': read index block " << f.indexBlock
                 << ", then go DIRECTLY to disk block " << f.blocks[i] << "\n";
            return;
        }
    cout << "File not found\n";
}

int main() {
    cout << "--- Indexed File Allocation (30-block disk) ---\n\n";
    create("alpha.txt", 5);
    create("beta.txt", 4);
    create("gamma.txt", 6);
    display();
    cout << "\nRandom access (no need to read previous blocks):\n";
    access("beta.txt", 2);
    access("gamma.txt", 5);
    cout << "\nDisk map ('#' = used, '.' = free):\n";
    for (int i = 0; i < DISK_BLOCKS; i++) cout << (used[i] ? '#' : '.');
    cout << endl;
    return 0;
}
