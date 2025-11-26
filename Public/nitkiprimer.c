//
// Created by drash on 11/24/25.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* odrediBroj(void* data) {
    int i;
    int me = *((int* ) data);
    printf("Jas sum %d\n", me);
    pthread_exit(NULL);
}
int main (int argc, char *argv[]) {
    int thread_id;
    pthread_t thread[5];
    int t;
    int threadData[5];
    for (t = 0; t < 5; t++) {
        threadData[t] = t;
        printf("Kreiram thread %d\n", t);
        thread_id = pthread_create(&thread[t], NULL, odrediBroj, (void*)&threadData[t]);
    }
    for (t = 0; t < 5 ; t++) {
        thread_id = pthread_join(thread[t], NULL);
    }
    printf("Site Threads zavrsija so rabota\n");
    pthread_exit(NULL);
    return 0;
}