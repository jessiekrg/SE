#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10
int ent = 0;

void *fonction1(void *arg){
    printf("Hello world! \n");
    pthread_exit(NULL);
}

void *fonction2(void *arg){
    int *entier = (int *)arg;
    printf("%d\n", *entier);
    pthread_exit(NULL);
}

void *fonction3(void *arg){
    srand(time(NULL));
    int *entier_2 = malloc(sizeof(int));
    *entier_2 = rand() % 100;
    printf("je suis le thread 3 \n");
    pthread_exit(entier_2); //pthread_t retourne un pointeur générériçque de tpe void* mais ce que tu lui passes peut être un pointeur vers n’importe quel type.
} /* le compilateur l'interprète comme un void */
/*cette valeur avec pthread_join, tu la récupères en tant que void, d'ou le cast * e*/

void *fonction4(void *arg){
    int *tableau = (int *)arg;
    int *moyenne = malloc(sizeof(int));
    *moyenne = 0;
    for (int i = 0; i < N; i++){
        *moyenne += tableau[i];
    }
    *moyenne = *moyenne / N;
    printf("la moyenne %d\n", *moyenne);
    pthread_exit(moyenne);
}



int main(){
    void * entier_2;
    void * moyenne;
    pthread_t t1, t2, t3, t4; 
    int tableau[N];
    /*l'identifiant du thread qui sera créé,*/

    /*entier aléatoire généré par le processus principal*/
    srand(time(NULL));
    int entier_1 = rand() % 100;


    for (int i = 0; i < N; i++){
        tableau[i] = rand()*100+1;
        printf("valeur ; %d", tableau[i]);
    }

    pthread_create(&t1,NULL,fonction1,NULL);
    pthread_create(&t2, NULL, fonction2, &entier_1);
    pthread_create(&t3, NULL, fonction3, NULL);
    pthread_create(&t4, NULL, fonction4, &tableau);

    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, (void**)&entier_2); /*tu reçois ce void * dans entier_2 (qui est un void *), et tu le castes en int * pour accéder à la valeur entière stockée.*/
    pthread_join(t4, &moyenne );

    int en = *(int *)entier_2;
    int mo = *(int *)moyenne;

    printf("je suis le processus principal , j'afficher l'entier suivant : %d\n ",en );

    return 0;


}