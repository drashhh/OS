//
// Created by drash on 11/24/25.
//
/*
Да се напише програма во C програмскиот јазик за работа со процеси и нитки. Програмата како аргументи од командна
линија добива имиња на датотеки во кои има вредности за различни крипто-валути. Во секоја посебна датотека има реални
вредности одделени со празно место од посебни крипто-валути. Името на датотеката е името на крипто-валутата. Главниот процес
треба да креира онолку низи со реални вредности колку што има датотеки (крипто-валути) наведни како аргументи од командна
линија и да ги смести во секоја низа одделните вредности прочитани од датотеката (најмногу 100 датотеки – криптовалути може да
се наведат). Потоа, главниот процес креира дете процес на кој му ги испраќа овие низи од крипто-валути и го чека дете процесот да
заврши.
Дете процесот најпрво треба да креира онолку нитки колку што има низи (крипто-валути), притоа секоја нитка пребарува посебна
низа (крипто-валута). Нитките низ низите треба да го најдат најголемото зголемување помеѓу две соседни вредности и враќа кое е
најголемото зголемување за соодветната крипто-валута. Откако ќе завршат сите нитки, главната нитка (дете-процес) за секоја
крипто-валута го печати името на крипто-валутата и колкаво е најголемото зголемување за истата

lista od datoteki u argv, kolku argc -1 tolku nizi (maks 100) i roditelo gi polni nizite (sekoja kripto) so floats,
deteto treba da gi dobie nizite i roditelo ceka da zavrse deteto
Deteto treba da kreira nitki za sekoja niza i sekoja nitka da gi sproreduva site sosedni vrednosti i da najde
najgolemo zgolemuvanje megju niv i da go vrne toa, koa zavrsat site nitki (deteto ja vrakja kripto valutata so najgolemo
zgolemuvanje i ja pecate vrednosta)
 */
#include <float.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

typedef struct {
    char ime[256];
    float* vrednosti;
    int brVrednosti;
    float najgolemaRazlika;
} KriptoPodatoci;
char buffer[4096] = "";
void* najdiRazlika(void * podatoci) {
    KriptoPodatoci *kripto = (KriptoPodatoci *) podatoci;
    if (kripto->brVrednosti < 2) {
        kripto->najgolemaRazlika =0.0f;
        return NULL;
    }
    float max_inc = -1.0f;

    for (int i =0; i < kripto->brVrednosti -1; i++) {
        float razlika = kripto->vrednosti[i+1] - kripto->vrednosti[i];
        if (razlika > max_inc) {
            max_inc = razlika;
        }
     }

    kripto->najgolemaRazlika = max_inc;
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    KriptoPodatoci podatoci[100];
    if (argc < 2) {
        printf("GRESKA: treba minium eden fajl so kriptovaluta!\n");
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        podatoci[i-1].brVrednosti = 0;
        strcpy(podatoci[i-1].ime, argv[i]);
        podatoci[i-1].vrednosti = malloc(100 * sizeof(float));

        FILE *fajl = fopen(argv[i], "r");
        if (fajl == NULL) {
            printf("Greska pri citanje fajl %s\n", argv[i]);
            return -1;
        }
        while (fscanf(fajl, "%f", &podatoci[i-1].vrednosti[podatoci[i-1].brVrednosti]) == 1) { //citaj float po float i zacuvuvaj u nizaKripto
            printf("Ja procitov %.2f \n", podatoci[i-1].vrednosti[podatoci[i-1].brVrednosti]);
            podatoci[i-1].brVrednosti++; //za sekoj broj zgolemuvaj
        }
        fclose(fajl); // zavrsena operacija so momentalen fajl
    }

    pid_t dete;
    dete = fork(); // tuka pocnuva kod za dete
    if (dete == 0){//tuka kod za dete
        pthread_t thread[100];
        int threadId;
        for (int i = 1; i < argc; i++) {
            threadId = pthread_create(&thread[i], NULL, najdiRazlika, &podatoci[i-1]);
        }
        for (int i = 1; i < argc; i++) {
            pthread_join(thread[i-1], NULL);
        }

        for (int i=0; i < argc-1; i++) {
            char linija[128];
            sprintf(linija, "Najgolemo zgolemuvanje kaj %s iznesuva: %.2f\n", podatoci[i].ime, podatoci[i].najgolemaRazlika);
            strcat(buffer, linija);
        }
        // for (int i = 1; i < argc; i++) {
        //     printf("Najgolemo zgolemuvanje kaj %s ima vo vrednost %.2f\n",
        //         podatoci[i-1].ime,
        //         podatoci[i-1].najgolemaRazlika);
        // }
    }
    pid_t deteEcho;
    deteEcho = fork();
    if (deteEcho == 0) {
        execlp("echo", "echo", "-e", buffer, (char*) NULL);
    }else { //kod za roditel
        wait(NULL);
        printf("Deteto zavrsi so rabota, jas se brisam.\n");
        for (int i = 0; i < argc-1; i++) {
            free(podatoci[i].vrednosti);
        }
        return 0;
    }

}
