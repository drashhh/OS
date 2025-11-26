//
// Created by drash on 11/24/25.
//
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>

int niza[1000], lokMax[10];
int max = -1;
void* napraviNiza(void *data){
    int iti = *(int *)data;
    for (int i = 0; i < 100; i ++) {
        niza[iti*100+i] = rand();
    }
    printf("Thread so %d uspesno gi napravi brojkite\n", iti);
    pthread_exit(NULL);
}
void* sortirajNiza(void *data) {
    int iti = *(int *)data;
    for (int i = 0; i < 100; i ++) {
        if (lokMax[iti] < niza[iti*100+i]) {
            lokMax[iti] = niza[iti*100+i];
        }
    }
}
int main (int argc, char *argv[]) {
    pthread_t thread[10];
    int threadId;
    int kojDel[10];
    for(int i = 0; i < 10; i++){
        lokMax[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        kojDel[i] = i;
        threadId = pthread_create(&thread[i], NULL, napraviNiza, &kojDel[i]);
    }
    for (int i = 0; i < 10; i++) {
        threadId = pthread_join(thread[i], NULL);
    }
    printf("Site threads zavrsija\n");
    printf("Pecatenje na niza\n");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", niza[i]);
    }
    for (int i = 0; i < 10; i++) {
        kojDel[i] = i;
        threadId = pthread_create(&thread[i], NULL, sortirajNiza, &kojDel[i]);
    }
    for (int i = 0; i < 10; i++) {
        threadId = pthread_join(thread[i], NULL);
    }
    printf("\nSite threads zavrsija so lokMaks\n");
    for (int i = 0; i < 10; i++) {
        printf("%d, ", lokMax[i]);
        if (lokMax[i] > max) {
            max = lokMax[i];
        }
    }
    printf("Maksimalen clen e %d\n", max);
}