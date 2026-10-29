// Experiment 9: Inter-Process Communication using Shared Memory (System V)
#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main() {
    key_t key = ftok(".", 'S');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);      // create shared memory segment
    if (shmid < 0) { perror("shmget"); return 1; }

    pid_t pid = fork();
    if (pid == 0) {
        // CHILD: attaches and writes a message
        char *mem = (char *)shmat(shmid, NULL, 0);
        const char *msg = "Hello from the child process through shared memory!";
        strcpy(mem, msg);
        cout << "[CHILD ] Written to shared memory : " << msg << endl;
        shmdt(mem);
        return 0;
    }

    // PARENT: waits for child then reads the message
    wait(NULL);
    char *mem = (char *)shmat(shmid, NULL, 0);
    cout << "[PARENT] Read from shared memory  : " << mem << endl;
    shmdt(mem);                                            // detach
    shmctl(shmid, IPC_RMID, NULL);                         // remove segment
    cout << "Shared memory segment removed." << endl;
    return 0;
}
