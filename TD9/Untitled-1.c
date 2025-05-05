
#include <stdio.h>      // Pour printf() et perror()
#include <sys/types.h>  // Pour les types de données comme mode_t
#include <sys/stat.h>   // Pour la structure stat et les macros S_IS*
#include <unistd.h>     // Pour l'appel système lstat()
#include <stdlib.h> 
#include <string.h>

#define MAX 1024
#define W_R 2

struct FICHIER {
    int fd; // descripteur de f
    int flags; //mode_ouverture
    char buf[MAX]; 
    int reste;
} ; 

FICHIER *fp;

typedef struct FICHIER FICHIER;

FICHIER *my_open(char *file, char *mode){
    int m; // mode d'ouverture pour open
    int f; // flags


    switch(mode[0]){

        case 'r' : 
            m = O_RDONLY;
            f = F_R;
            break;
        case 'w' :
            m = O_CREAT | O_TRUNC | O_WRONLY;
            f = F_W;
            break;
        default:
            return NULL;
    }

    fd  = open(file, m , 0666);
    if (fd == -1){
        return NULL;
    }

    fp = (FICHIER *)malloc(sizeof(fp));
    if (fp == NULL){
        return NULL;
    }

    
    return *FICHIER;
    
    return NULL;
}

int my_getc(FICHIER *fp){
    
}