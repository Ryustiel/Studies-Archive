#include <stdio.h>
#include <stdlib.h>
#define MAXP 10

typedef struct Pile {
    int tab[MAXP];
    int sommet;
} pile;

int pile_vide(pile p) {
    if (p.sommet == -1) {return 1;}
    return 0;
}

int pile_pleine(pile p) {
    if (p->sommet >= MAXP) {return 1;}
    return 0;
}

pile creer_pile() {
    pile p;
    p.sommet = -1;
    return p;
}

int empiler(pile * p, int val) {
    if (pile_pleine(p)) {
        printf("Erreur : la pile est pleine \n");
        return 0;
    } 
    p -> sommet++;
    p -> tab[p->sommet] = val;
    return 1;
}

int depiler(pile * p) {
    //int val;
    if(pile_vide(p)) {
        printf("Erreur : la pile est vide.\n")
        return INT_MAX; // signale une erreur
    }
    //val = p->tab[p->sommet];
    p->sommet--;
    //return val;
    return p->tab[p->sommet + 1]; // il suffit de pointer vers une autre case du tableau
}


typedef struct File {
    int tab[MAXP];
    int tete;
    int queue;
} file;

int file_vide(file *f) {
    return (f->tete == f->queue);
}

int file_pleine(file *f) {
    return (f->tete == (f->queue+1) % MAXP); // on traite pas fqueue mais on utilise cette operation pour infinite loop
}

file creer_file() {
    file f;
    f.tete = 0; // indice zero contient la valeur absente
    f.queue = 0;
    return f;
}

int enfiler(file *f, int val) {
    if (file_pleine(f)) {
        printf("Erreur : la file est pleine.\n");
        return 0;
    }
    f->tab[f->queue] = val;
    f->queue = (f->queue+1) % MAXP; // pour "revenir au debut"
    return 1;
}

int defiler(file *f) {
    int val;
    if (file_vide(f)) { // exceptions, exceptions et exceptions...
        printf("Erreur : la file est vide.\n");
        return INT_MAX;
    }
    val = f->tab[f->tete]; // du coup on cache la valeur
    f->tete = (f->tete + 1) % MAXP;

    //return f->tab[f->tete]; <- il aurait fallu s'assurer que l'ancienne tete est pas retour au depart qqch
    return val;
}



typedef struct Node {
    int val;
    struct cellule * pere;
    struct cellule * filsG;
    struct cellule * frereD;
} cellule;

cellule * creer_cellule(int x) {
    cellule * n = malloc(sizeof(cellule));
    n->val = x;
    return n; // voir la correction
}



