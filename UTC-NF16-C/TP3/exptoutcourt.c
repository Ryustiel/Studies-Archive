#include <stdio.h>

// rappels...
// element * tete; => liste_ligne tete;
// int ** tab;
// tab = malloc(3 * sizeof(int));
// (element *) * tab; // suite de pointeurs qui pointent vers des addresses d'elements
// en lisant le contenu refere par les elements du tableau, on obtient des adresses pour elements.

typedef struct element {
    int col;
    int value;
    struct element * next;
} element;

typedef struct liste_ligne {
    struct element * tete;
} liste_ligne;

typedef struct matrice_creuse {
    (struct liste_ligne) * tab;
    int Nlignes;
    int Ncolonnes;
} matrice_creuse;

void remplirMatrice(matrice_creuse * m, int N, int M) {
    matrice-> tab = malloc(sizeof(liste_ligne)); // allocating for "liste_ligne" array
}

void afficherMatrice(matrice_creuse m) {

}

void afficherMatriceListes(matrice_creuse m) {

}

int rechercherValeur(matrice_creuse m, int i, int j) {

}

void affecterValeur(matrice_creuse * m, int i, int j, int val) {

}

int main() {
    matrice_creuse m;
    remplirMatrice(m, 2, 2);
}