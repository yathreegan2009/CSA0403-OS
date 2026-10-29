// Experiment 1: Create a new process using fork() and display PID and PPID
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    cout << "Parent program started. PID = " << getpid() << endl;

    pid_t pid = fork();            // create a new process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "\n[CHILD ] My PID        : " << getpid()  << endl;
        cout << "[CHILD ] Parent's PID    : " << getppid() << endl;
    } else {
        // Parent process
        wait(NULL);                // wait for the child to finish
        cout << "\n[PARENT] My PID        : " << getpid() << endl;
        cout << "[PARENT] Child's PID     : " << pid << endl;
        cout << "[PARENT] My Parent's PID : " << getppid() << endl;
    }
    return 0;
}
