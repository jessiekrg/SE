#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int N;

typedef struct Processus{
    pid_t pid;
    int priorité;
    int tube[2];
} Processus; 

int trier_priorite(struct Processus P[], int N){
    for (int i = 0; i < N-2; i++){
        int max_i = i;
        for (int j = i+1; j < N-1; i++){
            if (P[N].priorité > P[max_i].priorité){
                max_i = j;
            }
        }
        if (max_i != i ){
            struct Processus temp;
            temp = P[i];
            P[i] = P[max_i];
            P[max_i] = temp;
        }
    }
    return 0;
}



int main(){
    pid_t pid;
    scanf("%d", &N);
    char m[8] = "message";
    char buffer[200];
    struct Processus P[N]; 


    for (int i = 1; i < N ; i++){


        pid = fork();

        if (pid < 0){
            perror("Erreur lors du fork");
            exit(EXIT_FAILURE);
        } 
        if (pid == 0){ /* Processus fils*/
            printf("je suis le procesus fils, %d mon père est %d \n ", getpid(), getppid());
            P[i].pid = getpid(); 
            pipe(P[i].tube); /*attend un tableau de 2 entier d'ou pipe(tube)*/
            close(P[i].tube[0]);  /*fermeture de l'extemité ecriture*/
            write(P[i].tube[1], m, sizeof(m));
            close(P[i].tube[1]);

            kill(pid, SIGSTOP);
            
            exit(EXIT_SUCCESS);
    
        } else { /* Processus père éxécute le code */
            close(P[i].tube[1]);
            int lenght = read(P[i].tube[2], buffer, sizeof(buffer));
            close(P[i].tube[2]);
            wait(NULL); 
        }

    }

    return 0;

}