#include <stdio.h>

// Renvoie l'indice de la première occurrence d’un caractère dans une chaîne
// Retourne -1 si le caractère n’est pas trouvé
int mon_strchr(char *chaine, int car){
    int compteur = 0;
    while (*chaine != '\0'){
        if (*chaine == car){
            return compteur; // retourne l'indice du caractère
        }
        chaine++;
        compteur++;
    }
    return -1; // caractère non trouvé
}

int main(){
    int a = mon_strchr("aaalola", 'l');
    if (a != -1) {
        printf("Indice du caractère trouvé : %d\n", a);
    } else {
        printf("Caractère non trouvé\n");
    }
    return 0;
}
