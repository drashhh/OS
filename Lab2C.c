#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>


void izvrsiKomanda(char *argv[]){
    execvp(argv[0], argv);
    perror("Greska pri execvp");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if(argc < 3){
        fprintf(stderr,"Koristi: <0 za parellelno, 1 za sekvencijalno> <naredba> [argumenti...]\n");
        exit(EXIT_FAILURE);
    }
    int N;
    printf("Vnesi broj za kolku pati da se izvrsi > ");
    scanf("%d", &N);

    if(N <= 0){
        fprintf(stderr, "Mora N da e pozitiven broj.");
        exit(EXIT_FAILURE);
    }
    int mode = atoi(argv[1]);
    char **argumenti = &argv[2];

    if(mode == 0){
        for(int i = 0; i < N; i++){
            pid_t pid = fork();
            if(pid<0){
                perror("Greska pri fork()");
                return -1;
            }else if(pid == 0){
                printf("Dete %d zapocnuva so izvrsuvanje\n", getpid());
                izvrsiKomanda(argumenti);
            }
        }
    }else if(mode == 1){
        printf("Se izvrsuvaat sekvencijalno %d procesi\n", N);
        for(int i = 0; i < N ; i++){
            pid_t pid = fork();
            if(pid<0){
                perror("Greska pri fork()");
                return -1;
            }else if(pid == 0){
                printf("Dete %d zapocnuva so izvrsuvanje\n", getpid());
                izvrsiKomanda(argumenti);
            }else{
                wait(NULL);
            }
        }
    }else{
        printf("Modot ne e izbran dobro! Mora da e 0 za Paralelno, 1 za Sekvencijalno!\n");
        return -1;
    }
    printf("Zavrsi prvicniot proces 0\n");
    

    return 0;
}
