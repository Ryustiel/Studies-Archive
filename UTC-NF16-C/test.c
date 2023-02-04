typedef struct Sommet {
    int cle;
    struct Sommet *fils_gauche;
    struct Sommet *fils_droit;
} T_Sommet;

typedef T_Sommet* T_Arbre;

T_Sommet* creerSommet(int cle) {
    T_Sommet* c = malloc(sizeof(T_Sommet));
    c->cle = cle;
    c->fils_gauche = NULL;
    c->fils_droit = NULL;
    return c;
}

void inserer(T_Arbre* A, int cle) {
    T_Sommet* y = NULL;
    T_Sommet* x = *A;
    
    while (x != NULL) {
        y = x;
        if (x->cle > y->cle) {
            x = x->gauche;
        }
        else {
            x = x->droit;
        }
    }

    if (y == NULL) { // gere le cas racine de l'arbre...
        *A = creerSommet(cle);
    }
    else {
        if (cle < y->cle) {
            y->gauche = creerSommet(cle);
        }
        else {
            y->droit = creerSommet(cle);
        }
    }
}

// pas de fils : simple detachement

// un seul fils : rattachement

// deux fils : recherche du successeur (on part du pere, on cherche la cle, 
// on va une fois a droite (superieurs), puis on spam a gauche (plus
// petit superieur)), ensuite on garde le predecesseur du pere. Ensuite
// on detache le successeur (suppression), et on le met a la place du
// pere

int main() {

}