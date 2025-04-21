#include <stdio.h>

//Définir une constante ou une macro ()
#define MAX_SIZE 50
#define SIZE 10

typedef struct structureA {
    char *ptr;
    int tab[SIZE];
    structureA *ptrA;
} structureA;

structureA *Tableau[MAX_SIZE];
