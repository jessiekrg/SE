#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*On souhaite généraliser l’exercice précédent à n processus : le premier passe les données depuis 
l’entrée standard au second, qui les passe au troisième, et ainsi de suite jusqu’au n-1-ème qui les 
passe au n-ème, qui les écrit sur sa sortie standard.  
1. Combien de tubes sont nécessaires pour réaliser cette généralisation ?  
2. Ecrire le programme qui réalise cette généralisation.*/

/* on creait un processus fils qui creeait a son tou un processus fil ... */




int main(int arg, char *argv[]){

    int n = atoi(argv[1]); //nombre de processus
    int N = n - 1; //nombre de tuyau
    int tube[N][2]; //déclaration du tableau de tubes
    char buffer[200];


    /*Création des tubes*/
    for (int i = 0; i < N; i++){
        pipe(tube[i]);
    }

    /*Créer les processus*/
    for (int i = 0; i < n ; i++){

        pid_t pid = fork();


        if (pid < 0){
            perror("Erreur lors du fork");
            exit(EXIT_FAILURE);
        }


        if (pid == 0){
            //si c'est pas le dernier processus
            if (i != n){
                dup2(tube[i][0], STDIN_FILENO); /*rediriger l'entrée standard (stdin) vers l'extrémité de lecture du tube*/ /*lecture car on lit c*/
                                                /* ON remplace l'entrée standard du processus par l'extrémité de lecture du tube (fd[0]*/

                //read(STDIN_FILENO, buffer, sizeof(buffer)); // Lire depuis l'entrée standard redirigée
                /*Je pourais utiliser scanf ou fgets (une fonction de lecture standard en bref)*/
            }

            //si c'est PAS PREMIER processus
            else if (i != 0){
                dup2(tube[i][1], STDOUT_FILENO); /*Redirirger la sortie standard (stdout) vers l'extremité écriture du tube */
            }

            //// Lecture depuis l'entrée standard et écriture vers la sortie standard
            int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
            write(STDOUT_FILENO, buffer, bytesRead);

            exit(EXIT_SUCCESS);


        }
    }

    // Fermeture de tous les descripteurs de fichiers dans le processus parent
    for (int i = 0; i < n - 1; i++) {
        close(tube[i][0]);
        close(tube[i][1]);
    }

    // Attente de la terminaison de tous les processus enfants
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }



    return 0;
}