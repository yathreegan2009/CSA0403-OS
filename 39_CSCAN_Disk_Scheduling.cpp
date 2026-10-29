// Experiment 39: C-SCAN (Circular SCAN) disk scheduling
// Head moves towards the end serving requests, jumps to the other end WITHOUT serving, and continues.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    vector<int> req = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, cylinders = 200;

    vector<int> left, right;
    for (int r : req) (r < head ? left : right).push_back(r);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "C-SCAN Disk Scheduling\n";
    cout << "Disk size: 0-" << cylinders - 1 << ", head: " << head << ", direction: towards higher cylinders\n";
    cout << "Request queue: "; for (int r : req) cout << r << " "; cout << "\n\n";

    vector<int> order;
    for (int r : right) order.push_back(r);
    order.push_back(cylinders - 1);          // reach the last cylinder
    order.push_back(0);                      // jump to the first cylinder
    for (int r : left) order.push_back(r);

    int total = 0, cur = head;
    cout << "Head movement:\n" << cur;
    for (int c : order) {
        if (cur == cylinders - 1 && c == 0) cout << " => 0 (jump)";       // jump counts as a return sweep
        else cout << " -> " << c;
        total += abs(c - cur);
        cur = c;
    }

    cout << "\n\nTotal head movement  : " << total << " cylinders (including the return jump)";
    cout << "\nAverage seek length  : " << (double)total / req.size() << endl;
    return 0;
}
