#include <stdio.h>

#define VALEUR 10

int lire_tableau(double *tableau, int max_elem, int *nb_elem) {
    double entree;
    *nb_elem = 0;

    for (int i = 0; i < max_elem; i++) {
        if (scanf("%lf", &entree) == 1) {
            *(tableau + *nb_elem) = entree;
            (*nb_elem)++;
        } else if (feof(stdin)) {
            break;
        } else {
            return -1;
        }
    }

    printf("Nombre réellement lus : %d\n", *nb_elem);
    return 0;
}

void trier_tableau(double *tableau, int nb_elem) {
    double *i, *j;
    double x;

    for (i = tableau + 1; i < tableau + nb_elem; i++) {
        x = *i;
        j = i;

        while (j > tableau && *(j - 1) > x) {
            *j = *(j - 1);
            j--;
        }

        *j = x;
    }
}

void affiche_tableau(double *tableau, int nb_elem) {
    double *p = tableau;
    double *fin = tableau + nb_elem;

    while (p < fin) {
        printf("%.2lf ", *p);
        p++;
    }
    printf("\n");
}

int main() {
    double tab[VALEUR];
    int nb_elem = 0;

    if (lire_tableau(tab, VALEUR, &nb_elem) == 0) {
        trier_tableau(tab, nb_elem);
        affiche_tableau(tab, nb_elem);
    } else {
        printf("Erreur de lecture.\n");
    }

    return 0;
}
