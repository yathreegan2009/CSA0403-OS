// Experiment 15: File organisation using a TWO LEVEL directory
// Master File Directory (MFD) -> User File Directory (UFD) -> files
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<string, vector<string>> mfd;       // user name -> list of files

void createUser(const string &u) {
    if (mfd.count(u)) cout << "User '" << u << "' already exists\n";
    else { mfd[u]; cout << "User directory '" << u << "' created\n"; }
}
void createFile(const string &u, const string &f) {
    if (!mfd.count(u)) { cout << "User '" << u << "' not found\n"; return; }
    auto &v = mfd[u];
    if (find(v.begin(), v.end(), f) != v.end()) cout << "File '" << f << "' already exists in " << u << "\n";
    else { v.push_back(f); cout << "File '" << f << "' created in " << u << "\n"; }
}
void deleteFile(const string &u, const string &f) {
    if (!mfd.count(u)) { cout << "User '" << u << "' not found\n"; return; }
    auto &v = mfd[u];
    auto it = find(v.begin(), v.end(), f);
    if (it == v.end()) cout << "File '" << f << "' not found in " << u << "\n";
    else { v.erase(it); cout << "File '" << f << "' deleted from " << u << "\n"; }
}
void searchFile(const string &u, const string &f) {
    if (mfd.count(u) && find(mfd[u].begin(), mfd[u].end(), f) != mfd[u].end())
        cout << "File '" << f << "' FOUND in " << u << "\n";
    else cout << "File '" << f << "' NOT found in " << u << "\n";
}
void display() {
    cout << "\nMaster File Directory\n";
    for (auto &p : mfd) {
        cout << "  |-- " << p.first << "/\n";
        for (auto &f : p.second) cout << "  |     |-- " << f << "\n";
    }
    cout << endl;
}

int main() {
    cout << "--- Two Level Directory Demo ---\n\n";
    createUser("alice");
    createUser("bob");
    createFile("alice", "resume.doc");
    createFile("alice", "photo.jpg");
    createFile("bob", "resume.doc");          // same name allowed for different users
    createFile("bob", "code.cpp");
    createFile("bob", "code.cpp");            // duplicate within same user
    createFile("carol", "x.txt");             // no such user
    display();
    searchFile("alice", "photo.jpg");
    searchFile("bob", "photo.jpg");
    deleteFile("alice", "resume.doc");
    display();
    return 0;
}
