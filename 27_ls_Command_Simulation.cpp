// Experiment 27: Simulating the ls UNIX command
// Usage: ./27            -> like  ls
//        ./27 -l [dir]   -> like  ls -l
//        ./27 -a [dir]   -> like  ls -a
//        ./27 -la [dir]  -> like  ls -la
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <cstring>
using namespace std;

string perms(mode_t m) {
    string s;
    s += S_ISDIR(m) ? 'd' : S_ISLNK(m) ? 'l' : '-';
    s += (m & S_IRUSR) ? 'r' : '-'; s += (m & S_IWUSR) ? 'w' : '-'; s += (m & S_IXUSR) ? 'x' : '-';
    s += (m & S_IRGRP) ? 'r' : '-'; s += (m & S_IWGRP) ? 'w' : '-'; s += (m & S_IXGRP) ? 'x' : '-';
    s += (m & S_IROTH) ? 'r' : '-'; s += (m & S_IWOTH) ? 'w' : '-'; s += (m & S_IXOTH) ? 'x' : '-';
    return s;
}

int main(int argc, char *argv[]) {
    bool longFmt = false, all = false;
    string path = ".";
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strchr(argv[i], 'l')) longFmt = true;
            if (strchr(argv[i], 'a')) all = true;
        } else path = argv[i];
    }

    DIR *d = opendir(path.c_str());
    if (!d) { perror("opendir"); return 1; }

    vector<string> names;
    struct dirent *e;
    while ((e = readdir(d)) != NULL)
        if (all || e->d_name[0] != '.') names.push_back(e->d_name);
    closedir(d);
    sort(names.begin(), names.end());

    for (auto &n : names) {
        if (!longFmt) { cout << n << "  "; continue; }
        struct stat st;
        string full = path + "/" + n;
        if (lstat(full.c_str(), &st) < 0) continue;
        struct passwd *pw = getpwuid(st.st_uid);
        struct group  *gr = getgrgid(st.st_gid);
        char tm[32];
        strftime(tm, sizeof(tm), "%b %d %H:%M", localtime(&st.st_mtime));
        cout << perms(st.st_mode) << " " << setw(3) << st.st_nlink << " "
             << setw(8) << (pw ? pw->pw_name : "?") << " " << setw(8) << (gr ? gr->gr_name : "?") << " "
             << setw(8) << st.st_size << " " << tm << " " << n << endl;
    }
    if (!longFmt) cout << endl;
    return 0;
}
