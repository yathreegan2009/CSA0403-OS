// Experiment 31: FIFO page replacement
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int frameCount = 3;

    vector<int> frames;
    queue<int> order;
    int faults = 0;

    cout << "FIFO Page Replacement  (Frames = " << frameCount << ")\n\n";
    cout << "Page | Frames          | Status\n";
    cout << "-----+-----------------+-------\n";

    for (int p : pages) {
        bool hit = find(frames.begin(), frames.end(), p) != frames.end();
        if (!hit) {
            faults++;
            if ((int)frames.size() < frameCount) { frames.push_back(p); order.push(p); }
            else {
                int victim = order.front(); order.pop();          // oldest page
                *find(frames.begin(), frames.end(), victim) = p;
                order.push(p);
            }
        }
        cout << "  " << p << "  | ";
        for (int i = 0; i < frameCount; i++) {
            if (i < (int)frames.size()) cout << frames[i] << " "; else cout << "- ";
        }
        cout << "          | " << (hit ? "Hit" : "Page Fault") << endl;
    }

    cout << "\nTotal pages     : " << pages.size();
    cout << "\nTotal page faults: " << faults;
    cout << "\nTotal page hits  : " << pages.size() - faults;
    cout << "\nHit ratio        : " << (double)(pages.size() - faults) / pages.size() << endl;
    return 0;
}
