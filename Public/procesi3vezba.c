//
// Created by drash on 11/24/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    clock_t start, end;
    pid_t dete;
    start = time(NULL);
    printf("Zapocnuvam so broenje na vreme.\n");
    if (argc < 2) {
        printf("Greska nemas dovolno argumenti! Mora barem 2!\n");
        return 1;
    }
    dete = fork();
    if (dete == 0) {
        execvp(argv[1], argv + 1);
    }else {
        waitpid(dete, NULL, 0);
        end = time(NULL);
        double vremePominato;
        vremePominato = (double)(end - start);
        printf("Deteto so PID: %d, zavrsi so izvrsuvanje na %s\n", dete, argv[1]);
        printf("Vreme pominato za izvrsuvanje %.2fs\n", vremePominato);
        return 0;
    }
}
