#include <stdio.h>      // Pour les fonctions d'entrée/sortie standard
#include <signal.h>     // Pour la gestion des signaux (non utilisée ici)
#include <time.h>       // Pour les fonctions liées au temps (non utilisée ici)
#include <fcntl.h>      // Pour les opérations de contrôle de fichiers (non utilisée ici)
#include <unistd.h>     // Pour les appels système Unix (fork, pipe, read, write, etc.)
#include <string.h>     // Pour les fonctions de manipulation de chaînes (non utilisée ici)
#include <stdlib.h>     // Pour les fonctions utilitaires générales (atoi, exit, etc.)
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static volatile sig_atomic_t taille = 0;

void gestionnaire_signal(int signum){
    if (signum == SIGINT){
        printf("signal receptionné \n ");
        printf("taille %d \n",taille);
        exit(0);
    }
}

int main(){
    int tube[2];
    char caract = 'A';
    pipe(tube);

    signal(SIGINT, gestionnaire_signal);

    while (1){
        ssize_t t = write(tube[1], &caract, sizeof(caract));
        if (t == -1){
            perror("Tube plein \n ");
            break;
        } else {
            taille += t;
        }
    }
    return 0;
}