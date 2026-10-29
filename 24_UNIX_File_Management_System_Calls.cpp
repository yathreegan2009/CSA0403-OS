// Experiment 24: UNIX system calls for file management
// open, write, read, lseek, close, link, rename, unlink, access, chmod
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
using namespace std;

int main() {
    const char *file = "demo_file.txt";
    char buf[100];

    // open() with O_CREAT and write()
    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }
    cout << "open()   : file '" << file << "' opened, file descriptor = " << fd << endl;

    const char *text = "UNIX system calls for file management";
    int w = write(fd, text, strlen(text));
    cout << "write()  : " << w << " bytes written" << endl;

    // lseek() back to the beginning and read()
    lseek(fd, 0, SEEK_SET);
    int r = read(fd, buf, sizeof(buf) - 1);
    buf[r] = '\0';
    cout << "read()   : " << r << " bytes read -> \"" << buf << "\"" << endl;

    // lseek() to an offset
    off_t pos = lseek(fd, 5, SEEK_SET);
    r = read(fd, buf, 14);
    buf[r] = '\0';
    cout << "lseek()  : moved to offset " << pos << ", read -> \"" << buf << "\"" << endl;
    close(fd);
    cout << "close()  : file closed" << endl;

    // access()
    cout << "access() : file " << (access(file, F_OK) == 0 ? "exists" : "does not exist") << endl;

    // chmod()
    chmod(file, 0600);
    cout << "chmod()  : permissions changed to 0600" << endl;

    // link()
    link(file, "demo_link.txt");
    cout << "link()   : hard link 'demo_link.txt' created" << endl;

    // rename()
    rename("demo_link.txt", "demo_renamed.txt");
    cout << "rename() : 'demo_link.txt' renamed to 'demo_renamed.txt'" << endl;

    // unlink()
    unlink("demo_renamed.txt");
    unlink(file);
    cout << "unlink() : both files deleted" << endl;
    return 0;
}
