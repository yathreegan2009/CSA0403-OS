// Experiment 14: File organisation using a SINGLE LEVEL directory
// All files of all users are kept in one directory, so names must be unique.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SingleLevelDir {
    string dirName;
    vector<string> files;
public:
    SingleLevelDir(string n) : dirName(n) {}
    void create(const string &f) {
        if (find(files.begin(), files.end(), f) != files.end())
            cout << "Error: file '" << f << "' already exists (names must be unique)\n";
        else { files.push_back(f); cout << "File '" << f << "' created\n"; }
    }
    void remove(const string &f) {
        auto it = find(files.begin(), files.end(), f);
        if (it == files.end()) cout << "Error: file '" << f << "' not found\n";
        else { files.erase(it); cout << "File '" << f << "' deleted\n"; }
    }
    void search(const string &f) {
        if (find(files.begin(), files.end(), f) != files.end()) cout << "File '" << f << "' FOUND\n";
        else cout << "File '" << f << "' NOT found\n";
    }
    void list() {
        cout << "\nDirectory: " << dirName << "\n";
        if (files.empty()) cout << "  (empty)\n";
        for (auto &f : files) cout << "  |-- " << f << "\n";
        cout << endl;
    }
};

int main() {
    SingleLevelDir root("root");
    cout << "--- Single Level Directory Demo ---\n\n";
    root.create("notes.txt");
    root.create("program.cpp");
    root.create("data.csv");
    root.create("notes.txt");       // duplicate name -> error
    root.list();
    root.search("program.cpp");
    root.search("report.doc");
    root.remove("data.csv");
    root.remove("missing.txt");
    root.list();
    return 0;
}
