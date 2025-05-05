#include <stdio.h>      // Pour printf() et perror()
#include <sys/types.h>  // Pour les types de données comme mode_t
#include <sys/stat.h>   // Pour la structure stat et les macros S_IS*
#include <unistd.h>     // Pour l'appel système lstat()
#include <stdlib.h>     // Pour exit()

// Fonction pour afficher le type de fichier
void afficher_type(mode_t mode) {
    if (S_ISREG(mode))      // Fichier régulier
        printf("-");
    else if (S_ISDIR(mode)) // Répertoire
        printf("d");
    else if (S_ISLNK(mode)) // Lien symbolique
        printf("l");
    else if (S_ISCHR(mode)) // Périphérique de caractère
        printf("c");
    else if (S_ISBLK(mode)) // Périphérique de bloc
        printf("b");
    else if (S_ISFIFO(mode)) // Tube nommé (FIFO)
        printf("p");
    else if (S_ISSOCK(mode)) // Socket
        printf("s");
    else                    // Type inconnu
        printf("?");
}

// Fonction pour afficher les permissions du fichier
void afficher_permissions(mode_t mode) {
    // Propriétaire
    printf((mode & S_IRUSR) ? "r" : "-"); // Lecture
    printf((mode & S_IWUSR) ? "w" : "-"); // Écriture
    printf((mode & S_IXUSR) ? "x" : "-"); // Exécution

    // Groupe
    printf((mode & S_IRGRP) ? "r" : "-"); // Lecture
    printf((mode & S_IWGRP) ? "w" : "-"); // Écriture
    printf((mode & S_IXGRP) ? "x" : "-"); // Exécution

    // Autres
    printf((mode & S_IROTH) ? "r" : "-"); // Lecture
    printf((mode & S_IWOTH) ? "w" : "-"); // Écriture
    printf((mode & S_IXOTH) ? "x" : "-"); // Exécution
}

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nom_du_fichier>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat infos; // Structure pour stocker les informations du fichier

    // Utilisation de lstat() pour obtenir les informations du fichier
    // lstat() est utilisé au lieu de stat() pour ne pas suivre les liens symboliques
    if (lstat(argv[1], &infos) == -1) {
        perror("Erreur lors de l'appel à lstat");
        exit(EXIT_FAILURE);
    }

    // Affichage du type et des permissions
    afficher_type(infos.st_mode);       // Type du fichier
    afficher_permissions(infos.st_mode);// Permissions
    printf("\n");                       // Nouvelle ligne

    return 0;
}
