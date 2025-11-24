#include <stdio.h>
#include <pthread.h>
int kolku[100];
char zbor[20];
typedef struct
{
    int id;
    char dat[20];
}info;

void *baraj(void *){

}

int main(int argc, char *argv[]){
    int type, N; char dat[3][20];
    if(argc == 1){
        scanf("%s", zbor);
    }else{
        strcpy(zbor, argv[1]);
    }
    if(argc > 2){
        N = argc - 2;
        type = 0;
    }else{
        N = 3;
        type = 1;
        for(int i = 0; i < 3; i++){
            scanf("%s", dat[i]);
        }
    }
    pthread_t nitki[N];
    info t[N];
    for(int i = 0; i < N; i++){
        t[i].id = i;
        //izbrisa ja tablata 
        if(type == 0){
            strcpy(t[i].dat, argv[i+2]);
        }else{
            strcpy(t[i].dat, dat[i]);
        }

    pthread_create(&nitki[i], NULL, (void*), &t[i]);
    }

}