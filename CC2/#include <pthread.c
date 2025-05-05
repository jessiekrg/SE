#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int compteur = 0;

void* barriere_reutilisable(void *arg) {
    [...]
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage : %s nb_threads\n", argv[0]);
        return 1;
    }

    nb_threads = atoi(argv[1]);
    pthread_t tid[nb_threads];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < nb_threads; ++i) {
        [...]
    }

    for (int i = 0; i < nb_threads; ++i) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
