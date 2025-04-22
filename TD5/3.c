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

    for (int i = 0; i<m; i++){
        pid = fork(); //le processus père créait m processus fils

        if (pid < 0){
            perror("Erreur lors du fork \n");
            exit(EXIT_FAILURE);
        
        } else if (pid == 0){ //le m processus fils créait n processus fils
            printf("Je suis le processus fils lvl = 1 de PID : %d dont le PID du père est : %d \n", getpid(), getppid());
            for (int j = 0; j < n; j++){
                pid = fork();

                if (pid < 0){
                    perror("Erreur lors du fork \n");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0){
                    printf("Je suis le processus fils lvl 2 de PID : %d dont le PID du père est : %d \n", getpid(), getppid());
                    exit(EXIT_SUCCESS);
                }

            }

            for (int j = 0; j < n; j++){ //Attente par le m processus fils la terminaison du n processus fils
                wait(NULL);
            }

            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i<m; i++){
        wait(NULL);
    }

    return 0;

}



int Fonction_recursive(int m, int n, int niveau_max, int *compteur ){
    //vérification du niveau
    if (m == niveau_max){
        return 0;
    } else {
        for ( int i = 0; i < n ; i++ ){
            pid_t pid = fork();

            if (pid == 0){
                printf("Processus de PID : %d du niveau %d, dont les père est : %d \n", getpid(), m, getppid());
                Fonction_recursive(m+1, n, niveau_max);
                exit(1);
            } else {
                wait(NULL);
                compteur++;
            }


        }

    }
    return compteur;
}


int P3(int m, int n){
    Fonction_recursive(0,n,m);
    exit(0);
    return 0;
}

int main(int argc, char *argv[]){

    if (argc != 3){
        perror("Erreur de saisie \n");
        exit(EXIT_FAILURE);
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    //P1(m,n);
    //P2(m,n);
    P3(m,n);

    return 0;

}