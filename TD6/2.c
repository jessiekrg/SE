/* Exercice 2 : boucle infinie avec SIGINT et SIGTERM */

#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

volatile sig_atomic_t compteur = 0;
volatile sig_atomic_t terminer = 0;

void gestionnaire_signal(int signum) {
    int fd = open("fichier.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    if (signum == SIGINT) {
        time_t maintenant = time(NULL);
        struct tm *temps = localtime(&maintenant);

        char buffer[256];
        int len = snprintf(buffer, sizeof(buffer),
            "Signal SIGINT reçu à %02d:%02d:%02d, compteur = %d\n",
            temps->tm_hour, temps->tm_min, temps->tm_sec, compteur);

        write(fd, buffer, len);
    } else if (signum == SIGTERM) {
        const char *fin = "fin\n";
        write(fd, fin, strlen(fin));
        terminer = 1;
    }

    close(fd);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = gestionnaire_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    while (!terminer) {
        compteur++;
        sleep(1);
    }

    return 0;
}

