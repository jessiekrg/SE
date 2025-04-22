#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*Un  processus  père  crée  un  processus  fils  qui  compte  de  1  à  5  (affichage  par  seconde). 
Trois seconde après sa création, le processus fils est mis en pause par le processus père, 
qui le relancera après avoir attendu cinq secondes*/

int main(){
    int compteur = 0;
    pid_t pid = 0;
    pid = fork();

    if (pid < 0){
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0){
        for (int i = 0; i <= 5; i++){
            sleep(1);
            printf("Affichage de la %d \n", i);
        }
        exit(EXIT_SUCCESS);

    } else {
        sleep(3);
        kill(pid, SIGSTOP);
        sleep(5);
        kill(pid, SIGCONT);

        wait(NULL);
    }

    return 0;

}