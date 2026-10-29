// Experiment 37: First Come First Served (FCFS) disk scheduling
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main() {
    vector<int> req = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, cylinders = 200;

    cout << "FCFS Disk Scheduling\n";
    cout << "Disk size: 0-" << cylinders - 1 << ", initial head position: " << head << "\n";
    cout << "Request queue: "; for (int r : req) cout << r << " "; cout << "\n\n";

    int total = 0, cur = head;
    cout << "Head movement:\n" << cur;
    for (int r : req) {
        int d = abs(r - cur);
        cout << " -> " << r;
        total += d;
        cur = r;
    }
    cout << "\n\nSeek distances: ";
    cur = head;
    for (int r : req) { cout << abs(r - cur) << " "; cur = r; }
    cout << "\n\nTotal head movement  : " << total << " cylinders";
    cout << "\nAverage seek length  : " << (double)total / req.size() << endl;
    return 0;
}
