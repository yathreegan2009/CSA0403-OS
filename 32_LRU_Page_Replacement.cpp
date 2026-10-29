// Experiment 32: LRU (Least Recently Used) page replacement
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int frameCount = 3;

    vector<int> frames, lastUsed;
    int faults = 0;

    cout << "LRU Page Replacement  (Frames = " << frameCount << ")\n\n";
    cout << "Page | Frames          | Status\n";
    cout << "-----+-----------------+-------\n";

    for (int t = 0; t < (int)pages.size(); t++) {
        int p = pages[t];
        auto it = find(frames.begin(), frames.end(), p);
        bool hit = it != frames.end();

        if (hit) lastUsed[it - frames.begin()] = t;
        else {
            faults++;
            if ((int)frames.size() < frameCount) { frames.push_back(p); lastUsed.push_back(t); }
            else {
                int lru = min_element(lastUsed.begin(), lastUsed.end()) - lastUsed.begin();  // oldest use time
                frames[lru] = p; lastUsed[lru] = t;
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
