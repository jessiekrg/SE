#include <stdio.h>

#define VALEUR 100

int lire_tableau(double *tableau, int max_elem, int *nb_elem){ // *tableau : 
    double entree;
    for (int i = 0; i<max_elem; i++){
        if (scanf("%lf", &entree) == 1){ //scanf va utiliser cette adresse pour écrire dedans
            *tableau = entree;
            tableau++;
            (*nb_elem)++;
        } else if (scanf("%lf", &entree) == EOF){
            break;
        } else {
            return -1;
        }
    }
    printf("nombre réellement lus : %lf" , *nb_elem );
    return 0;
};


void trier_tableau(double *tableau, int nb_elem){
    int *i, *j;
        int x;

        for (i = tableau + 1; (i < tableau + nb_elem); i++) {
            x = *i;
            j = i;

            // Tant que l'élément précédent est plus grand que x
            while (j > tableau && *(j - 1) > x) {
                *j = *(j - 1); // Décaler l'élément vers la droite
                j--;
            }

            *j = x; // Insérer x à sa place
        }
    }

void affiche_tableau(double *tableau, int nb_elem){
    for (int i = 0; i < nb_elem;i++){
        printf(*(tableau + i));
    }

}


int main(){

    double *(tab + 10);

    if (lire_tableau(tab, 10, 0) == 0){
        trier_tableau(tab,10);
        affiche_tableau(tab,10);
        
    }

    return 0;

}