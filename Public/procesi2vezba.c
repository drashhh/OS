//
// Created by drash on 11/24/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        ferror("Nemas dovolno argumenti");
        return 1;
    }
    bool pozadinski = false;
    for (int i = 1; i < argc; i++) {
        if (strchr(argv[i], '&') != NULL) {
            pozadinski = true;
            break;
        }
    }
    pid_t dete;
    dete = fork();
    if (dete == 0) {
        execvp(argv[1], argv + 1);
        ferror("Greska pri execvp\n");
        return 1;
    }else {
        int status;
        if (waitpid(dete, &status, 0)<0) {
            ferror("Greska pri waitpid\n");
        }else {
            printf("Deteto so PID: %d, zavrsi.\n", dete);
        }
        wait(NULL);
    }


}
