#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*Ecrire  un  programme  composé  de  deux  processus :  le  premier  lit  des  données  sur  l’entrée 
standard et les passe par un tube au deuxième qui les affiche sur sa sortie standard.*/
int main(){
    char buffer[100];
    int pipefd[2];
    pid_t pid;

    pipe(pipefd);

    pid = fork();

    if (pid < 0){
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(pipefd[0]);
        printf("Je suis le fils de PID : %d , ecrit qqchs : \n", getpid());
        int n = read(STDIN_FILENO, buffer, sizeof(buffer)); /*je lis ce qui est saisie depuis l'entrée standard et j'affecte la taille e la saisie à n*/
        //buffer est un tampon où seront stockées les données lues.
        write(pipefd[1], buffer, n); 
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Je suis le père de PID %d , le tube receptionné contient %s \n ", getpid(), buffer);
        close(pipefd[0]);
        wait(NULL);
    }

    return 0;

}