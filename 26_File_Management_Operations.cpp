// Experiment 26: File management operations
// create, write, read, append, copy, rename, size, delete
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

void showFile(const string &name) {
    ifstream in(name);
    string line;
    cout << "  ---- " << name << " ----\n";
    while (getline(in, line)) cout << "  " << line << endl;
    cout << "  ----------------------\n";
}

int main() {
    string f1 = "file_a.txt", f2 = "file_b.txt", f3 = "file_c.txt";

    // 1. Create & write
    ofstream out(f1);
    out << "Line 1: Operating Systems\nLine 2: File management\n";
    out.close();
    cout << "1. File '" << f1 << "' created and written\n"; showFile(f1);

    // 2. Append
    ofstream app(f1, ios::app);
    app << "Line 3: This line was appended\n";
    app.close();
    cout << "\n2. Data appended to '" << f1 << "'\n"; showFile(f1);

    // 3. Copy
    ifstream src(f1, ios::binary);
    ofstream dst(f2, ios::binary);
    dst << src.rdbuf();
    src.close(); dst.close();
    cout << "\n3. '" << f1 << "' copied to '" << f2 << "'\n";

    // 4. Rename
    rename(f2.c_str(), f3.c_str());
    cout << "4. '" << f2 << "' renamed to '" << f3 << "'\n";

    // 5. File size
    ifstream sz(f3, ios::ate | ios::binary);
    cout << "5. Size of '" << f3 << "' = " << sz.tellg() << " bytes\n";
    sz.close();

    // 6. Count lines, words, characters
    ifstream cnt(f3);
    string w; int words = 0, lines = 0, chars = 0; string ln;
    while (getline(cnt, ln)) { lines++; chars += ln.size() + 1; }
    cnt.clear(); cnt.seekg(0);
    while (cnt >> w) words++;
    cout << "6. Lines = " << lines << ", Words = " << words << ", Characters = " << chars << "\n";

    // 7. Delete
    remove(f1.c_str());
    remove(f3.c_str());
    cout << "7. Both files deleted\n";

    ifstream chk(f1);
    cout << "   Does '" << f1 << "' still exist? " << (chk.good() ? "Yes" : "No") << endl;
    return 0;
}
