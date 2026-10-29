// Experiment 10: Inter-Process Communication using Message Queue (System V)
#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

struct Message {
    long type;
    char text[100];
};

int main() {
    key_t key = ftok(".", 'Q');
    int msqid = msgget(key, IPC_CREAT | 0666);            // create message queue
    if (msqid < 0) { perror("msgget"); return 1; }

    pid_t pid = fork();
    if (pid == 0) {
        // CHILD = sender
        Message m;
        m.type = 1;
        for (int i = 1; i <= 3; i++) {
            snprintf(m.text, sizeof(m.text), "Message number %d from child", i);
            msgsnd(msqid, &m, sizeof(m.text), 0);
            cout << "[SENDER  ] Sent    : " << m.text << endl;
        }
        return 0;
    }

    // PARENT = receiver
    wait(NULL);
    Message r;
    for (int i = 0; i < 3; i++) {
        msgrcv(msqid, &r, sizeof(r.text), 1, 0);
        cout << "[RECEIVER] Received: " << r.text << endl;
    }
    msgctl(msqid, IPC_RMID, NULL);                         // delete queue
    cout << "Message queue removed." << endl;
    return 0;
}
