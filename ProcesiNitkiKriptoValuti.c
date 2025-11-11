#include <stdio.h>
#include <pthread.h>

int kripto[100][1000];
int N[100];
float max[100];

//Funkcijata ja naogja nagolemata zgolemuvacka za sekoja kripto valuta

void *funk(void *t){
    int x = *((int *)t);
    int m = 0; 
    for(int i = 0; i < N[x]-1; i++){
        if(kripto[x][i+1] > kripto[x][i]){
            int p = kripto[x][i+1] - kripto[x][i];
            if(p > m)
                m = p;
        }
        max[x] = m; // mozno e da treba nadvor od for cikluso
        pthread_exit(m); // i ovoa
    }

}

int main(int argc, char *argv[]){
    FILE *f;
    int L = argc-1;
    if(L < 2){
        printf("Greshka pri vlez.");
        return 0;
    }
    for(int i = 0; i < L; i++){
        f = fopen(argv[i+1], "r");
        if(f == NULL)
            continue;
        N[i] = 0;
        while(fscanf(f, "%f ", &kripto[i][N[i]]) && !eof(f)){
            N[i]++;
        }
        fclose(f);
    }
    pid_t dete = fork();
    if(dete){
        wait(NULL);
        return 0;
    }
    pthread_t nitki[L]; int t[L];
    for(int i = 0; i < L; i++){
        t[i] = i;
        pthread_create(&nitki[i], NULL, funk, (void *)&t[i]);

    }
    for(int i = 0; i < L; i++){
        pthread_join(nitki[i], NULL);   
    }
    //Bonus namesto printf da se pecati so echo preku shell komanda
    char niza[100];
    for(int i = 0; i < L; i++){
        strcpy(niza, argv[i+1]);
        ftoa(niza+strlen(niza), max[i]);
        dete = fork();
        if(dete == 0){
            execlp("echo", "echo", niza, NULL); //execlp?
        }
    }
    //Obicen nastan
    for(int i = 0; i < L; i++){
        printf("Za valuta %S, max zgolemuvanje %f\n", argv[i+1], max[i]);
        return 0;
    }
}