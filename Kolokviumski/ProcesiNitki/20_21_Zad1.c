//
// Created by drash on 11/25/25.
//
// Да се напише програма во C која работи со процеси и нитки. Главната програма (родител процесот)
// пополнува низа од 1000 броеви на случаен начин со помош на rand() функцијата. Потоа, креира два
// деца процеси, така што, двата деца процеси вршат пребарување на бројот 0 во низата од 1000 броеви.
// Првото дете процес, пребарувањето го прави со помош на 10 деца процеси, додека пак второто дете,
// пребарувањето го прави со 10 нитки. Секоја нитка/дете процес добива дел од низата што треба да го
// пребара бројот 0 и печати на екран колку пати е пронајден бројот кај соодветната нитка/дете процес.
// Родител процесот чека да завршат двете деца процеси и на екран печати кое од двете завршило прво.
// Доколку прво заврши дете процесот кое пребарувањето го прави со помош на деца процеси, тогаш на
// екран се печати „pobrzo zavrshi prebaruvanjeto so deca procesi“, инаку печати „pobrzo zavrsi prebaruvanjetopobrzo zavrshi prebaruvanjeto so deca procesi“,
// инаку печати „pobrzo zavrshi prebaruvanjeto so deca procesi“, инаку печати „pobrzo zavrsi prebaruvanjetopobrzo zavrsi prebaruvanjeto
// so nitki“.
// БОНУС: Да се имплементира кодот така што двете деца процеси печатат само по еднаш колку вкупно е
// пронајдена 0. Кај првото дете процес, комуникацијата со децата процеси кои пребаруваат да се прави со
// помош на датотека со име „pobrzo zavrshi prebaruvanjeto so deca procesi“, инаку печати „pobrzo zavrsi prebaruvanjetocommunicate.txt“

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int nizaBrojki[1000];
int kojPrv = 0;
int brojacNitki = 0, brojacDeca = 0;

void* presmetajNuli(void* data) {
    int nitkaBroj = *(int*)data;
    printf("Uspesno zapocnata nitka %d prebaruvam...\n", nitkaBroj);
    for (int i = nitkaBroj*100; i < nitkaBroj*100+100; i++) {
        if (nizaBrojki[i] == 0) {
            brojacNitki++;
            printf("Nitkata pronajde nula\n");
        }
    }
    pthread_exit(NULL);
}
int main(int argc, char* argv[]) {
    printf("Zapocnuvam so generiranje na 1000 random brojki\n");
    for (int i = 0; i < 1000; i++) {
        nizaBrojki[i] = rand()%100;
    }
    pid_t deteNitki;
    pid_t deteDeca;
    deteNitki = fork();
    if (deteNitki == 0) {
        pthread_t nitki[10];
        int nitkaId[10];
        int nitkaRedBr[10];
        for (int i = 0; i < 10; i++) {
            nitkaRedBr[i] = i;
            nitkaId[i] = pthread_create(&nitki[i], NULL, presmetajNuli, &nitkaRedBr[i]);
        }
        for (int i=0; i < 10; i++) {
            nitkaId[i] = pthread_join(nitki[i], NULL);
        }
        if (kojPrv == 0) kojPrv = 1;
        printf("Nitkite zavrsija\n");
        _exit(0); //za deteNitki
    }else {
        deteDeca = fork();
        if (deteDeca == 0) {
            printf("Zapocnuva prebaruvanjeto so deca\n");
            pid_t decaDete[10];
            for (int i = 0; i <10; i++) { //pravenje na decata na deteto
                decaDete[i] = fork();
                if (decaDete[i] == 0) {
                    for (int j = i*100; j < i*100+100; j++) {
                        if (nizaBrojki[j] == 0) {
                            printf("Deteto pronajde nula\n");
                        }
                    }
                    printf("Deteto %d zavrsi so prebaruvanje...\n", i);
                    _exit(0);
                }else {
                    //del za dete kako roditel ne pravi nisto
                }
            }
            for (int i = 0; i < 10; i++) { //cekaj da zavrsat site
                waitpid(decaDete[i], NULL, 0);
            }
            if (kojPrv == 0) kojPrv = 2;
            printf("Decata zavrsija\n");
            _exit(0); //za deteDeca
        }else { //roditel
            printf("....\n");
            int prv = wait(NULL);
            if (prv == deteNitki) {
                printf("Pobrzi bea NITKITEEE\n");
            }else {
                printf("Pobrzi bea DECATAAA\n");
            }
            wait(NULL);
        }
    }

}

