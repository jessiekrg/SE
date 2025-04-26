#include <stdio.h>      // Pour les fonctions d'entrée/sortie standard
#include <signal.h>     // Pour la gestion des signaux (non utilisée ici)
#include <time.h>       // Pour les fonctions liées au temps (non utilisée ici)
#include <fcntl.h>      // Pour les opérations de contrôle de fichiers (non utilisée ici)
#include <unistd.h>     // Pour les appels système Unix (fork, pipe, read, write, etc.)
#include <string.h>     // Pour les fonctions de manipulation de chaînes (non utilisée ici)
#include <stdlib.h>     // Pour les fonctions utilitaires générales (atoi, exit, etc.)

/*
Objectif : Généraliser la communication entre n processus.
Le premier lit depuis l'entrée standard et transmet les données au second,
qui les transmet au troisième, et ainsi de suite jusqu'au dernier processus,
qui écrit les données sur la sortie standard.
*/

int main(int arg, char *argv[]) {

    int n = atoi(argv[1]); // Convertit l'argument en entier : nombre de processus
    int N = n - 1;          // Nombre de tubes nécessaires (un de moins que le nombre de processus)
    int tube[N][2];         // Tableau pour stocker les descripteurs de fichiers des tubes
    char buffer[200];       // Tampon pour stocker les données lues/écrites

    /* Création des tubes */
    for (int i = 0; i < N; i++) {
        pipe(tube[i]); // Crée un tube : tube[i][0] pour la lecture, tube[i][1] pour l'écriture
    }

    /* Création des processus */
    for (int i = 0; i < n; i++) {

        pid_t pid = fork(); // Crée un nouveau processus

        if (pid < 0) {
            perror("Erreur lors du fork"); // Affiche une erreur si le fork échoue
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Processus enfant

            // Si ce n'est pas le premier processus, rediriger l'entrée standard
            if (i != 0) {
                dup2(tube[i - 1][0], STDIN_FILENO); // Redirige l'entrée standard vers l'extrémité de lecture du tube précédent
            }

            // Si ce n'est pas le dernier processus, rediriger la sortie standard
            if (i != n - 1) {
                dup2(tube[i][1], STDOUT_FILENO); // Redirige la sortie standard vers l'extrémité d'écriture du tube actuel
            }

            // Lecture depuis l'entrée standard et écriture vers la sortie standard
            int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer)); // Lit les données depuis l'entrée standard
            write(STDOUT_FILENO, buffer, bytesRead); // Écrit les données vers la sortie standard

            exit(EXIT_SUCCESS); // Termine le processus enfant
        }
    }

    // Fermeture de tous les descripteurs de fichiers dans le processus parent
    for (int i = 0; i < n - 1; i++) {
        close(tube[i][0]); // Ferme l'extrémité de lecture du tube
        close(tube[i][1]); // Ferme l'extrémité d'écriture du tube
    }

    // Attente de la terminaison de tous les processus enfants
    for (int i = 0; i < n; i++) {
        wait(NULL); // Attend la fin d'un processus enfant
    }

    return 0; // Termine le processus parent
}
