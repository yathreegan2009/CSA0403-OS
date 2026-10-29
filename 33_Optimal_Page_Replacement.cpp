// Experiment 33: Optimal page replacement
// Replaces the page that will not be used for the longest time in the future.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int frameCount = 3, n = pages.size();

    vector<int> frames;
    int faults = 0;

    cout << "Optimal Page Replacement  (Frames = " << frameCount << ")\n\n";
    cout << "Page | Frames          | Status\n";
    cout << "-----+-----------------+-------\n";

    for (int t = 0; t < n; t++) {
        int p = pages[t];
        bool hit = find(frames.begin(), frames.end(), p) != frames.end();

        if (!hit) {
            faults++;
            if ((int)frames.size() < frameCount) frames.push_back(p);
            else {
                int victim = -1, farthest = -1;
                for (int i = 0; i < frameCount; i++) {
                    int next = n;                                  // n = never used again
                    for (int k = t + 1; k < n; k++)
                        if (pages[k] == frames[i]) { next = k; break; }
                    if (next > farthest) { farthest = next; victim = i; }
                }
                frames[victim] = p;
            }
        }
        cout << "  " << p << "  | ";
        for (int i = 0; i < frameCount; i++) {
            if (i < (int)frames.size()) cout << frames[i] << " "; else cout << "- ";
        }
        cout << "          | " << (hit ? "Hit" : "Page Fault") << endl;
    }

    cout << "\nTotal pages     : " << n;
    cout << "\nTotal page faults: " << faults;
    cout << "\nTotal page hits  : " << n - faults;
    cout << "\nHit ratio        : " << (double)(n - faults) / n << endl;
    return 0;
}
