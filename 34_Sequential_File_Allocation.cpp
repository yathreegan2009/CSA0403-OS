// Experiment 34: Sequential file allocation
// Records are stored one after another (physically and logically).
// To access record k, all previous records 1..k-1 must be read first.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int DISK_BLOCKS = 30;
bool used[DISK_BLOCKS] = {false};

struct File { string name; int start, length; };
vector<File> directory;

bool allocate(const string &name, int length) {
    // find 'length' contiguous free blocks
    for (int i = 0; i + length <= DISK_BLOCKS; i++) {
        bool free = true;
        for (int j = i; j < i + length; j++) if (used[j]) { free = false; break; }
        if (free) {
            for (int j = i; j < i + length; j++) used[j] = true;
            directory.push_back({name, i, length});
            cout << "File '" << name << "' allocated: start block = " << i << ", length = " << length
                 << "  (blocks " << i << " to " << i + length - 1 << ")\n";
            return true;
        }
    }
    cout << "File '" << name << "' could NOT be allocated (no contiguous space of " << length << " blocks)\n";
    return false;
}

void accessRecord(const string &name, int record) {
    for (auto &f : directory) {
        if (f.name != name) continue;
        if (record < 1 || record > f.length) { cout << "Record " << record << " does not exist in " << name << "\n"; return; }
        cout << "Accessing record " << record << " of '" << name << "' -> reading blocks: ";
        for (int i = 0; i < record; i++) cout << f.start + i << " ";
        cout << "\n   (all " << record - 1 << " previous record(s) had to be read first)\n";
        return;
    }
    cout << "File '" << name << "' not found\n";
}

void showDisk() {
    cout << "\nDisk map ('#' = used, '.' = free):\n";
    for (int i = 0; i < DISK_BLOCKS; i++) cout << (used[i] ? '#' : '.');
    cout << "\n\nDirectory:\nFile        Start   Length\n";
    for (auto &f : directory) cout << f.name << string(12 - f.name.size(), ' ') << f.start << "       " << f.length << "\n";
}

int main() {
    cout << "--- Sequential File Allocation (30-block disk) ---\n\n";
    allocate("report.txt", 5);
    allocate("data.dat", 8);
    allocate("notes.txt", 4);
    allocate("video.mp4", 20);       // too big -> fails
    showDisk();
    cout << "\n";
    accessRecord("data.dat", 4);
    accessRecord("report.txt", 1);
    accessRecord("notes.txt", 9);
    return 0;
}
