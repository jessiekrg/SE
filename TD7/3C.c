#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static volatile sig_atomic_t taille = 0;

void gestionnaire_signal(int signum){
    if (signum == SIGINT){
        printf("\nSignal SIGINT reçu\n");
        printf("Taille atteinte avant blocage : %d octets\n", taille);
        exit(0); // Quitter proprement après affichage
    }
}

int main(){
    int tube[2];
    char caract = 'A';

    if (pipe(tube) == -1){
        perror("Erreur pipe");
        return 1;
    }

    signal(SIGINT, gestionnaire_signal);

    while (1){
        ssize_t res = write(tube[1], &caract, sizeof(caract));
        if (res == -1){
            perror("Tube plein");
            break;
        } else {
            taille += res;
        }
    }

    return 0;
}
