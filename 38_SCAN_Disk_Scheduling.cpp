// Experiment 38: SCAN (Elevator) disk scheduling
// Head moves in one direction serving requests until the end of the disk, then reverses.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    vector<int> req = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, cylinders = 200;
    bool towardsHigh = true;                    // initial direction

    vector<int> left, right;
    for (int r : req) (r < head ? left : right).push_back(r);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "SCAN Disk Scheduling\n";
    cout << "Disk size: 0-" << cylinders - 1 << ", head: " << head << ", direction: towards "
         << (towardsHigh ? "higher" : "lower") << " cylinders\n";
    cout << "Request queue: "; for (int r : req) cout << r << " "; cout << "\n\n";

    vector<int> order;
    if (towardsHigh) {
        for (int r : right) order.push_back(r);
        order.push_back(cylinders - 1);                       // go to the end of disk
        for (int i = left.size() - 1; i >= 0; i--) order.push_back(left[i]);
    } else {
        for (int i = left.size() - 1; i >= 0; i--) order.push_back(left[i]);
        order.push_back(0);
        for (int r : right) order.push_back(r);
    }

    int total = 0, cur = head;
    cout << "Head movement:\n" << cur;
    for (int c : order) { total += abs(c - cur); cur = c; cout << " -> " << c; }

    cout << "\n\nTotal head movement  : " << total << " cylinders";
    cout << "\nAverage seek length  : " << (double)total / req.size() << endl;
    return 0;
}
