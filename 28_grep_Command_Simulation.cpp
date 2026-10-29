// Experiment 28: Simulating the grep UNIX command
// Usage: ./28 [-n] [-i] [-c] pattern file
//        (no arguments -> runs a demo on a sample file)
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

string lower(string s) { transform(s.begin(), s.end(), s.begin(), ::tolower); return s; }

int main(int argc, char *argv[]) {
    bool showNum = false, ignoreCase = false, countOnly = false;
    string pattern, file;

    if (argc < 3) {
        // demo mode
        file = "grep_sample.txt";
        ofstream o(file);
        o << "Operating system manages hardware\nProcess scheduling is important\n"
             "Memory management is a key task\nThe OPERATING system uses a kernel\n"
             "File systems store data\n";
        o.close();
        pattern = "operating"; ignoreCase = true; showNum = true;
        cout << "[Demo] Equivalent to:  grep -n -i operating grep_sample.txt\n\n";
    } else {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-n")) showNum = true;
            else if (!strcmp(argv[i], "-i")) ignoreCase = true;
            else if (!strcmp(argv[i], "-c")) countOnly = true;
            else if (pattern.empty()) pattern = argv[i];
            else file = argv[i];
        }
    }

    ifstream in(file);
    if (!in) { cerr << "grep: cannot open " << file << endl; return 1; }

    string line, key = ignoreCase ? lower(pattern) : pattern;
    int ln = 0, matches = 0;
    while (getline(in, line)) {
        ln++;
        string cmp = ignoreCase ? lower(line) : line;
        if (cmp.find(key) != string::npos) {
            matches++;
            if (!countOnly) {
                if (showNum) cout << ln << ":";
                cout << line << endl;
            }
        }
    }
    if (countOnly) cout << matches << endl;
    else cout << "\n(" << matches << " matching line(s) found)" << endl;
    return 0;
}
