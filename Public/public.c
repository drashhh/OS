#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    pid_t dete[3];
    int i;
    for (i = 0; i < 3; i++) {
        dete[i] = fork();
        if (dete[i] == 0) break;
    }
    if (i < 3) {
        printf("Jas sum dete %d, so PID: %d, i roditel PPID: %d\n", i, getpid(), getppid());
    }else {
        for (i = 0; i < 3; i++) {
            wait(NULL);
        }
    }

    return 0;

}