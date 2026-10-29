// Experiment 2: Copy content of one file to another using system calls
// System calls used: open(), read(), write(), close()
// Usage: ./02 [source] [destination]   (no args -> demo files are used)
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
    const char *src = "source.txt", *dst = "destination.txt";
    if (argc >= 3) { src = argv[1]; dst = argv[2]; }
    else {
        // create a demo source file
        int d = open(src, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        const char *text = "Operating Systems Lab\nThis file is copied using system calls.\n";
        write(d, text, strlen(text));
        close(d);
    }

    int in = open(src, O_RDONLY);
    if (in < 0) { perror("open source"); return 1; }
    int out = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { perror("open destination"); return 1; }

    char buf[1024];
    ssize_t n, total = 0;
    while ((n = read(in, buf, sizeof(buf))) > 0) {
        write(out, buf, n);
        total += n;
    }
    close(in);
    close(out);
    cout << "Copied " << total << " bytes from '" << src << "' to '" << dst << "'" << endl;

    // show the copied content
    cout << "\n--- Content of " << dst << " ---\n";
    int f = open(dst, O_RDONLY);
    while ((n = read(f, buf, sizeof(buf))) > 0) write(STDOUT_FILENO, buf, n);
    close(f);
    return 0;
}
