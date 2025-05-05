#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int compteur = 0;
int N = 10; // 3 threads

void *fonction_thread(void *arg) {
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex);

    compteur++;

    if (compteur < N) {
        printf("Thread %d : j'attends que tout le monde arrive.\n", id);
        pthread_cond_wait(&cond, &mutex);
        printf("Thread %d : réveillé et je continue.\n", id);
    } else {
        printf("Thread %d : je suis le dernier, je réveille tout le monde !\n", id);
        pthread_cond_broadcast(&cond);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, fonction_thread, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
