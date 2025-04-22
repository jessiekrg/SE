#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>



int main(){
    int nb;
    pid_t pid;
    srand(time(NULL));
    int statut;

    for (int i = 1; i < 10; i++){

        pid = fork();

        if (pid < 0){
            perror("Erreur lors du forl \n");
            exit(EXIT_FAILURE);
        }

        if (pid == 0){
            nb = rand() % 10+1;
            sleep(nb);
            printf("Mon PID est : %d, celui de mon père est %d \n", getpid(), getppid());
            exit(nb); //le fils se termine
        }

        }

    for (int i = 1; i < 10; i++){
        pid_t valeur = wait(&statut);
        if (WIFEXITED(statut)){
            printf("le PID arrêté : %d et celui du père est %d , le fils a dormi %d secondes \n", valeur, getpid(), WEXITSTATUS(statut));
        }
    }
    
    
    return 0;
}