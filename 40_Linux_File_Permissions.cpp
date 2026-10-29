// Experiment 40: File access permissions and types of users in Linux
// Users: Owner (u), Group (g), Others (o)     Permissions: Read (r=4), Write (w=2), Execute (x=1)
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <iomanip>
using namespace std;

string rwx(mode_t m, mode_t r, mode_t w, mode_t x) {
    string s;
    s += (m & r) ? 'r' : '-';
    s += (m & w) ? 'w' : '-';
    s += (m & x) ? 'x' : '-';
    return s;
}

void show(const char *file) {
    struct stat st;
    stat(file, &st);
    mode_t m = st.st_mode;
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    cout << "File: " << file << "\n";
    cout << "  Symbolic : " << (S_ISDIR(m) ? 'd' : '-')
         << rwx(m, S_IRUSR, S_IWUSR, S_IXUSR) << rwx(m, S_IRGRP, S_IWGRP, S_IXGRP)
         << rwx(m, S_IROTH, S_IWOTH, S_IXOTH) << endl;
    cout << "  Octal    : " << oct << setw(4) << setfill('0') << (m & 0777) << dec << setfill(' ') << endl;
    cout << "  Owner(u) : " << (pw ? pw->pw_name : "?") << "  ->  " << rwx(m, S_IRUSR, S_IWUSR, S_IXUSR) << endl;
    cout << "  Group(g) : " << (gr ? gr->gr_name : "?") << "  ->  " << rwx(m, S_IRGRP, S_IWGRP, S_IXGRP) << endl;
    cout << "  Others(o): " << "everyone else  ->  " << rwx(m, S_IROTH, S_IWOTH, S_IXOTH) << endl << endl;
}

int main() {
    cout << "=== Linux File Permissions ===\n\n";
    cout << "Types of users : u = Owner, g = Group, o = Others, a = All\n";
    cout << "Permissions    : r = read (4), w = write (2), x = execute (1)\n";
    cout << "Example 755    : owner rwx (7), group r-x (5), others r-x (5)\n\n";

    const char *file = "perm_demo.txt";
    ofstream(file) << "permission demo\n";

    umask(022);
    chmod(file, 0644); cout << "[chmod 644]\n"; show(file);
    chmod(file, 0755); cout << "[chmod 755]\n"; show(file);
    chmod(file, 0600); cout << "[chmod 600] (only owner can read/write)\n"; show(file);
    chmod(file, 0444); cout << "[chmod 444] (read only for everyone)\n"; show(file);

    cout << "Access check for current user (access() system call):\n";
    cout << "  Read    : " << (access(file, R_OK) == 0 ? "allowed" : "denied") << endl;
    cout << "  Write   : " << (access(file, W_OK) == 0 ? "allowed" : "denied") << endl;
    cout << "  Execute : " << (access(file, X_OK) == 0 ? "allowed" : "denied") << endl;

    cout << "\nEquivalent shell commands:\n";
    cout << "  chmod 755 file      chmod u+x file      chmod g-w file      chmod o=r file\n";
    cout << "  chown user:group file     ls -l file     umask 022\n";

    chmod(file, 0644);
    unlink(file);
    return 0;
}
