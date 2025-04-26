
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;
int compteur = 0;

void *fonction_incremente(void *arg){ /*Fonction éxécutée par les thread*/

    pthread_mutex_lock(&mutex);
    compteur++; /*variable partagée, donc ca ne sert à rien de faire : int *compteur = malloc(sizeof(int));  // ❌ Mauvais : chaque thread a son propre compteur local → non partagé *compteur = 0;*/
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(){


    int nbThreads = 5;

    scanf("%d", &nbThreads);
    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*nbThreads); /*void *malloc(size_t taille_en_octets);*/


    /*ne pas oublier le free*/

    for (int i = 0; i < nbThreads ; i++){
        pthread_create(&threads[i], NULL, fonction_incremente, NULL);
    }

    for (int i = 0; i < nbThreads; i++){
        pthread_join(threads[i], NULL);
    }

    printf("le compteur est à %d \n ", compteur);
    pthread_mutex_destroy(&mutex);
    free(threads);

    return 0;

}