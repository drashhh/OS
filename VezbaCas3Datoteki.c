#include <stdio.h>

int kolku[100];
char zbor[20];

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
}