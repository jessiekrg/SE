#include <stdio.h>
#include <unistd.h> //fork
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/times.h>


int main(){

    struct tms start_time, end_time;
    clock_t real_start, real_end;

    // Mesure du temps avant fork
    real_start = times(&start_time);

    pid_t pid = fork();
    int fd = 0;


    if (pid == 0){
        fd = open("/dev/null", O_CREAT | O_WRONLY, 0777); //fichier descripteur (int)
        if (fd == - 1){
            perror("Erreur lors de l'ouverture de descripteur de fichier");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO); //va dupliquer le descripteur de fichier fd (celui de /dev/null) et le placer à la place du descripteur STDOUT_FILENO (la sortie standard). Autrement dit, la sortie standard (printf, ls, etc.) va désormais écrire dans /dev/null au lieu du terminal.
        close(fd);

        char *argv[] = {"ls", NULL}; //arguments
        execv("/bin/ls", argv); //remplace le programme courant par le par un nouveau programme situé a ... 

        perror("execv");
        exit(EXIT_FAILURE);

    } else {
        wait(NULL);

        real_end = times(&end_time);

        long ticks_per_second = sysconf(_SC_CLK_TCK);

        // Affichage du temps utilisateur et système du fils
        printf("Temps utilisateur : %.2f secondes\n", 
               (double)(end_time.tms_cutime - start_time.tms_cutime) / ticks_per_second);
        printf("Temps système : %.2f secondes\n", 
               (double)(end_time.tms_cstime - start_time.tms_cstime) / ticks_per_second);
        printf("Temps réel (mur) : %.2f secondes\n", 
               (double)(real_end - real_start) / ticks_per_second);
    }


    return 0;

}