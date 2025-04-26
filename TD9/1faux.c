#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

// ✅ OK : initialisation d’un mutex global
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *fonction_incremente(void *arg){ // ✅ OK : fonction thread
    int *compteur = malloc(sizeof(int));  // ❌ Mauvais : chaque thread a son propre compteur local → non partagé
    *compteur = 0;
    
    pthread_mutex_lock(&mutex);
    *compteur++; // ❌ ERREUR : *compteur++ = mauvaise syntaxe
    // 👉 Cela veut dire : (compteur++) → puis on déréférence l’ancien pointeur → ce qui est incorrect ici
    // ✅ Ce que tu veux : (*compteur)++;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(compteur); // ❌ Pas utile ici si tu veux un compteur **global partagé**
}

int main(){
    int nbThreads;
    void *compteur;

    // ❌ Mauvais usage de scanf : pas de format de lecture
    // scanf("Saisie le nombre de threads N \n", &nbThreads);
    // ✅ Correction :
    printf("Saisie le nombre de threads N \n");
    scanf("%d", &nbThreads);

    // ✅ Allocation dynamique correcte du tableau de threads
    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*nbThreads); 

    // ✅ Ne pas oublier le free plus bas (bien vu !)

    for (int i = 0; i < nbThreads ; i++){
        // ❌ Tu réutilises `threads` au lieu d’écrire &threads[i]
        pthread_create(threads, NULL, fonction_incremente, NULL);
        // ✅ Correction : pthread_create(&threads[i], NULL, fonction_incremente, NULL);
    }

    for (int i = 0; i < nbThreads; i++){
        // ❌ Même problème ici : tu ne parcours pas le tableau
        pthread_join(threads, &compteur);
        // ✅ Correction : pthread_join(threads[i], &compteur);
        // ❌ Autre problème : tu écrases `compteur` à chaque boucle → tu n'auras que le retour du dernier thread
    }

    // ❌ Ici tu penses afficher un compteur global, mais tu n’as en fait qu’un compteur local retourné par UN thread
    int valeur = *(int *)compteur;

    printf("le compteur est à %d \n", valeur);

    pthread_mutex_destroy(&mutex);
    free(threads); // ✅ Bien vu

    return 0;
}
