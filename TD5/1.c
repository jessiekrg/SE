#include <stdio.h>
#include <unistd.h> //fork
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>



int Afficher(){
    pid_t pid;

    pid = fork(); // crée une copie du processus appelant

    if (pid < 0){
        printf("Erreur lors du fork");
        return -1;
    }

    if (pid == 0){
        printf("Mon PID est %d , celui de mon père est %d \n", getpid(), getppid());
    } else {
        printf("Mon PID est %d , celui de mon fils est %d \n", getpid(), pid);
    }
    return 1;
}

int Afficher3(){
    int f;
    srand(time(NULL));
    pid_t pid;
    pid = fork(); // crée une copie du processus appelant
    int statut;

    if (pid < 0){
        printf("Erreur lors du fork \n");
        return -1;
    }

    if (pid == 0){
        int nb = rand() % 50 + 1;
        printf("nombre %d \n", nb);
        exit(nb);
    } else {
        wait(&statut); //
        if (WIFEXITED(statut)) {
            int received = WEXITSTATUS(statut);
            printf("Père : Le fils m'a envoyé %d \n", received);
        }
    }
    return 0;
}

int main(){
    Afficher();
    Afficher3();



}