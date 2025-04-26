
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int *entier; //variable partagée
int tour = 0;

void *fonction_productrice(void *arg){

    pthread_mutex_lock(&mutex); /*pas sûr de pk on l'utilise là*/
    //int *entier = (int *)malloc(sizeof(int)); /*cast void* en un int**/
    *entier = rand() % 100 + 1; 
    pthread_cond_signal(&cond); 
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *fonction_consommatrice(void *arg){

    pthread_mutex_lock(&mutex);
    while ( *entier == 0){
        pthread_cond_wait(&cond, &mutex);
    }
    printf("dernier thread %d \n", *entier);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *fonction_cp(void *arg){
    int rang = *(int *)arg;
    pthread_mutex_lock(&mutex);

    // ➡️ Attendre que ce soit son tour
    while (tour != rang) {
        pthread_cond_wait(&cond, &mutex);
    }

    // ➡️ Une fois réveillé et que c'est son tour :
    printf("Thread %d a reçu : %d\n", rang, *entier);

    // ➡️ Passer le tour au prochain thread
    tour++;

    // ➡️ Réveiller tous les autres pour vérifier s'ils peuvent agir
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int arg, char *argc[]){ //int atoi(const char *str)
    
    if (arg != 2){
        perror("Il faut saisir n \n ");
        exit(EXIT_FAILURE);
    }

    int N = atoi(argc[1]);

    entier = (int *)malloc(sizeof(int));
    *entier = 0; // pour éviter que les consommateurs voient n'importe quoi

    int *rangs = (int*)malloc(N * sizeof(int)); // Tableau pour stocker tous les rangs

    
    /*  Intitalisation des threads  */
    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*N);
    srand(time(NULL));

    for (int i = 0; i < N; i++){ 
        rangs[i] = i;
        if (i == 0){ /*C'est le premier thread*/
            pthread_create(&threads[i], NULL, fonction_productrice, &rangs[i]);
        } else if (i == N-1) { /*c'est le dernier thread*/
            pthread_create(&threads[i], NULL, fonction_consommatrice, &rangs[i]);
        } else { /* C'est ni le premier  ni le dernier thread*/
            pthread_create(&threads[i], NULL, fonction_cp, &rangs[i] );
        }
    }

    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    free(entier);
    free(threads);
    free(rangs);

    return 0;
}