// Experiment 25: I/O system calls of UNIX - fcntl, lseek, stat, opendir, readdir
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>
#include <cstring>
using namespace std;

int main() {
    const char *file = "io_demo.txt";
    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    const char *data = "0123456789ABCDEFGHIJ";
    write(fd, data, strlen(data));

    // ---------- fcntl ----------
    int flags = fcntl(fd, F_GETFL);
    cout << "--- fcntl() ---\n";
    cout << "File status flags : " << flags << (flags & O_RDWR ? " (opened read/write)" : "") << endl;
    fcntl(fd, F_SETFL, flags | O_APPEND);
    cout << "O_APPEND flag set : " << ((fcntl(fd, F_GETFL) & O_APPEND) ? "yes" : "no") << endl;
    int dupfd = fcntl(fd, F_DUPFD, 10);
    cout << "Duplicated descriptor (F_DUPFD) = " << dupfd << endl;
    close(dupfd);
    fcntl(fd, F_SETFL, flags);

    // ---------- lseek ----------
    cout << "\n--- lseek() ---\n";
    char c;
    lseek(fd, 10, SEEK_SET);
    read(fd, &c, 1);
    cout << "Character at offset 10 from start : " << c << endl;
    lseek(fd, -3, SEEK_END);
    read(fd, &c, 1);
    cout << "Character 3 bytes before the end  : " << c << endl;
    off_t size = lseek(fd, 0, SEEK_END);
    cout << "File size using lseek             : " << size << " bytes" << endl;
    close(fd);

    // ---------- stat ----------
    cout << "\n--- stat() ---\n";
    struct stat st;
    stat(file, &st);
    cout << "File name      : " << file << endl;
    cout << "Size           : " << st.st_size << " bytes" << endl;
    cout << "Inode number   : " << st.st_ino << endl;
    cout << "Hard links     : " << st.st_nlink << endl;
    cout << "Permissions    : " << oct << (st.st_mode & 0777) << dec << endl;
    cout << "Owner UID      : " << st.st_uid << endl;
    cout << "Last modified  : " << ctime(&st.st_mtime);

    // ---------- opendir / readdir ----------
    cout << "\n--- opendir() / readdir() --- (current directory)\n";
    DIR *dir = opendir(".");
    struct dirent *e;
    while ((e = readdir(dir)) != NULL)
        cout << "  " << e->d_name << (e->d_type == DT_DIR ? "/" : "") << endl;
    closedir(dir);

    unlink(file);
    return 0;
}
