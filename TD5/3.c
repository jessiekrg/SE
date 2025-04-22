#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>


int P1(int m, int n){

    pid_t pid;
    int compteur = 0;

    for ( int i = 0; i < m ; i++){
        for (int j = 0; j < n ; j++){

            pid = fork(); // crée une copie du processus appelant

            if (pid < 0){
                perror("Erreur lors du fork");
                return -1;
            }

            if (pid == 0) {
                printf("Je suis le %dème processus fils de PID : %d \n", compteur, getpid());
                exit(0);
            }
        }
    }

    for (int i = 0; i < m*n ; i++){
        wait(NULL);
    }

    return 0;


}


int P2(int m, int n){

    pid_t pid;
    int compteur = 0;

    

}

int main(int argc, char *argv[]){

    if (argc != 3){
        perror("Erreur de saisie \n");
        exit(EXIT_FAILURE);
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    P1(m,n);

    return 0;

}