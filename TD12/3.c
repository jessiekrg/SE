#include <stdio.h>      // Pour printf() et perror()
#include <sys/types.h>  // Pour les types de données comme mode_t
#include <sys/stat.h>   // Pour la structure stat et les macros S_IS*
#include <unistd.h>     // Pour l'appel système lstat()
#include <stdlib.h> 
#include <string.h>


int main(int arg, char *argv[]){

    struct stat stbuf;
    char *type;
    int mask; 
    char *p; // pointeur position 
    char protection[9+1]; // stocker les permission 
    
    if (arg != 2){
        perror("Erreur de saisie \n");
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], &stbuf) != 0){ /*récupération du fichier dont on va récupere les informations et les retranscrire stbuf un pointeur vers une structure de type stat */
        perror("ERREUR lors l'éxécution stat"); /* retourne 0 si succès */
        return 0;
    }

    switch (stbuf.st_mode & S_IFMT){ /*masque pour identifier le type de fichier*/
        case (S_IFREG):
            type = "Fichier normal \n";
            break;

        case (S_IFDIR):
            type = "Répertoire \n";
            break;

        case (S_IFCHR):
            type = "Fichier spécial \n ";
            break;
        
        case (S_IFLNK):
            type = "Lien symbolique";
            break;

        case (S_IFIFO):
            type = "Tube nommé";
            break;
        
        default : 
            type = "???";
            break;
    
    }


    strcpy(protection, "rwxrwxrwx");
    p = protection ;
    
    mask = 00400; // S_IRUSR 

    while (mask != 0 ) {
        if ((stbuf.st_mode & mask) == 0 ){
            *p = '-';
        }
        mask >>= 1; /* Décalage de 1 bit vers la droite */
        p++;
    }

    printf ("type : %s \n",  type);
    printf( " %s\t type : %s\t permission : %s \n" , argv[1], type, protection);
    return 0;

}