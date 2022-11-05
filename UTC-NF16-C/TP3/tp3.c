#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"
#include <math.h>


// Fonction qui permet de creer un element d'une liste chainee
// Params : indice de colonne (int), valeur de l'element (int)
// Return : pointeur vers le nouvel element cree
element *creerElement(int colonne, int valeur) {
    element *nouvelElement = malloc(sizeof(element));
    nouvelElement->col = colonne;
    nouvelElement->val = valeur;
    nouvelElement->suivant = NULL;
    return nouvelElement;
}


void remplirMatrice(matrice_creuse *m, int N, int M) {

  m->tab_lignes = malloc(sizeof(liste_ligne) * N);
  m->Nlignes = N;
  m->Ncolonnes = M;

  element * previous; // adresse de l'element precedent
  int i=0, j=0, inpt; // store les nombres ou les caracteres saisis
  while (i < N) {
    j=0;
    m->tab_lignes[i] = NULL;
    previous = NULL; // valeur initiale a chaque nouvelle ligne

    while (j < M) {
      for (int k=0; k<20; k++) {printf("\n");}
      afficherMatrice(*m); // affiche l'etat actuel de la matrice a l'utilisateur (confort)
      printf("Filling (%d %d)...\ngoto shortcuts : (b) previous line, (l) beginning of current line, (s) next line (fills current with zeros)\n> ", i, j); // ADDON (8)
      
      if (scanf("%d", &inpt)) {
        if (inpt) { // checks if input was an integer
          element * e = creerElement(j, inpt); // cree un element zero
          if (previous == NULL) {m->tab_lignes[i] = e;} // initialise la liste chainee
          else {previous->suivant = e;}
          previous = e;
        }
        j++;
      }
      else {
        if (getchar() == 's') { // saisie non entier
            if (i<N) {i++;} // remplie la ligne avec des zeros
            j = 0;
            previous = NULL;
            break;
        }
        while (getchar() != '\n');
    }

    i++;
  }
}


void afficherMatrice(matrice_creuse m) {
  int i, j;
    for (i=0; i < m.Nlignes; i++) {
        liste_ligne ligne = m.tab_lignes[i]; //ligne pointe vers l'element actuellement lu
        for (j=0; j < m.Ncolonnes; j++) {
            //si l'element ne correspond pas a la colonne, on affiche 0
            if (ligne == NULL || ligne->col > j) {
                printf("0      ");
            }
            //sinon on affiche la valeur de l'element
            else {
                element el = *ligne;
                printf("%d ", el.val);

                //on determine la taille de la chaine ecrite pour ajouter le bon nombre d'espace (esthetique)
                int length;
                if (el.val > 0) {
                    length = (int)log10(el.val);
                }
                else {
                    length = 1 + (int)log10(- el.val);
                }
                for (length; length < 5; length++) {
                    printf(" ");
                }
                ligne = el.suivant;
            }
        }
        printf("\n"); //a la fin de la ligne, retour a la ligne
    }
}



void afficherMatriceListes(matrice_creuse m) {
    int i;
    for (i=0; i < m.Nlignes; i++) {
        liste_ligne ligne = m.tab_lignes[i]; //ligne pointe vers l'element actuellement lu
        printf("Ligne %d :", i);
        //pour chaque element, on affiche la valeur et la colonne
        while (ligne != NULL) {
            printf(" Colonne : %d, Valeur : %d -->", ligne->col, ligne->val);
            ligne = ligne->suivant;
        }
        printf(" NULL\n");
    }
}



int rechercherValeur(matrice_creuse m, int i, int j) {
  
  int value = 0; // valeur par defaut si la chaine n'existe pas (= vrai zero) ou si valeurs i, j invalides

  if (i < m.Nlignes && j < m.Ncolonnes) { // verifie si la position saisie est valide
    element * e = m.tab_lignes[i];
    while (e != NULL && e->col > j) { // parcours la liste chainee d'indice i jusqu'a eventuellement trouver la colonne associee
      if (e->col == j) {
        value = e->val;
        break;
      }
      e = e->suivant;
    }
  }
  
  return value;

}


void affecterValeur(matrice_creuse m, int i, int j, int val) {
    if (i < m.Nlignes && j < m.Ncolonnes) {
        element *e = m.tab_lignes[i];
        element *prec = e;
        if (val == 0) { // un zero doit etre insere
            if (e != NULL) { // si la chaine est deja vide, aucune action n'est declenchee
                if (e->col == j) {
                    m.tab_lignes[i] = e->suivant; // retire la node (tete de chaine)
                    free(e); // supprime l'ancienne tete de chaine
                }
                else {
                    while (e != NULL) {
                        if (e->col == j) { // retire la node actuelle de la chaine si elle correspond
                            prec->suivant = e->suivant;
                            free(e); // supprime la node intermediaire "e"
                        }
                        prec = e;
                        e = e->suivant;
                    }
                }
            }
        }
        else { // un nombre non nul doit etre insere
            if (e == NULL) {
                m.tab_lignes[i] = creerElement(j, val); // insere directement la node (tete de chaine)
            }
            else if (m.tab_lignes[i]->col > j) { // la tete de la chaine est remplacee
                element *e2 = creerElement(j, val);
                e2->suivant = m.tab_lignes[i];
                m.tab_lignes[i] = e2;
            }
            else { // la tete de la chaine est necessairement inferieure ou egale a la colonne
                do {
                    if (e->col == j) { // on tombe sur la bonne colonne
                        e->val = val;
                        break;
                    }
                    else if (e->col > j) {  // la valeur est depassee, on insere la node sur le precedent
                                            // ne se declenche jamais a la premiere iteration (la tete est inferieure ou egale a e->col)
                        element *e2 = creerElement(j, val);
                        e2->suivant = e;
                        prec->suivant = e2;
                        break;
                    }
                    else if (e->suivant == NULL) { // pas de suivant, on insere a la fin de la chaine
                        element *e2 = creerElement(j, val);
                        e->suivant = e2;
                        break;
                    }
                    prec = e;
                    e = e->suivant;
                } while (e != NULL);
            }
        }
    }
}
 
 



void additionerMatrices(matrice_creuse m1, matrice_creuse m2) {

  if (m1.Nlignes == m2.Nlignes && m1.Ncolonnes == m2.Ncolonnes) { // verifie si la matrice est valide
  element * e1; // sera utilise pour iterer sur chaque matrice
  element * e2;
  element * prev; // utilisee pour inserer des elements de m2 dans m1

    for (int i = 0; i < m1.Nlignes; i++) {
      if (m2.tab_lignes[i] != NULL) { // pas besoin d'alterer la ligne de m1 si celle de m2 est vide

        e1 = m1.tab_lignes[i];
        e2 = m2.tab_lignes[i];
        prev = e1;

        if (e1 == NULL) { // la ligne de m1 est vide mais pas celle de m2, on copie les elements de la ligne de m2 dans m1
          m1.tab_lignes[i] = creerElement(e2->col, e2->val); // premiere valeur e2 mise en tete de chaine
          e2 = e2->suivant;
          while (e2 != NULL) { // e2 stocke la valeur qui doit etre attribuee a e1->suivant a cause de l'affectation de la ligne precedente
            e1->suivant = creerElement(e2->col, e2->val);
            e1 = e1->suivant;
            e2 = e2->suivant;
          }
        }
        else { // m1 et m2 non null, additionne les valeurs la ou elles coincident, integre l'element de m2 dans m1 sinon
          while (e2 != NULL && e1 != NULL) { // itere sur les valeurs de la ligne de m2, les valeurs sont stockees dans m1
            if (e1->col == e2->col) {
              if (e1->val + e2->val == 0) {
                prev->suivant = e1->suivant;
                free(e1); // suppression du maillon dans m1, car sa valeur est zero 
              } 
              else {
                e1->val = e1->val + e2->val; // addition des valeurs dans le maillon de m1
              }

              e2 = e2->suivant;
              prev = prev->suivant;
              e1 = prev->suivant->suivant;
            }
            else if (e2->col < e1->col) { // insere les valeurs de e2 en tete de liste chainee
              if (e1 == m1.tab_lignes[i]) { // prev == e1 dans ce cas
                m1.tab_lignes[i] = creerElement(e2->col, e2->val);
                m1.tab_lignes[i]->suivant = e1;
                prev = m1.tab_lignes[i];
              }
              else { // la valeur doit etre inseree entre prev et e1
                prev->suivant = creerElement(e2->col, e2->val);
                prev->suivant->suivant = e1;
                prev = prev-> suivant; // (prev->col < e1->col) reste vraie
              }
              
              e2 = e2->suivant;
            }
            else {e1 = e1->suivant;} // (e1->col < e2->col), continuer d'iterer jusqu'a atteindre l'endroit ou inserer e2
          // prev->col < e2->col
          }
          // la derniere valeur prise par e2 n'a pas encore ete rattachee a m1, ou alors elle est NULL
          while (e2 != NULL) {
            prev->suivant = creerElement(e2->col, e2->val);
            prev = prev->suivant;
            e2 = e2->suivant;
          }
        }
      }

    } 
  }
}


int nombreOctetsGagnes(matrice_creuse m) {
    int taille_m, taille_non_creuse;
    //taille en memoire avec une representation classique
    taille_non_creuse = m.Ncolonnes * m.Nlignes * sizeof(int);

    //taille en memoire avec la representation utilisee
    taille_m = m.Nlignes * sizeof(liste_ligne) + 2 * sizeof(int); //espace occupe par m.tab_lignes, m.Ncolonnes et m.Nlignes
    int i;
    liste_ligne ligne;
    for (i=0; i < m.Nlignes; i++) {
        ligne = m.tab_lignes[i];
        //pour chaque element de la liste, on ajoute la taille d'un element
        while (ligne != NULL) {
            taille_m += sizeof(element);
            ligne = ligne->suivant;
        }
    }
    return taille_non_creuse - taille_m; //retour de la difference
}


void supprimerMatrice(matrice_creuse m) {
    int i;
    liste_ligne ligne, previous;
    for (i=0; i < m.Nlignes; i++) {
        ligne = m.tab_lignes[i];
        //suppression des elements
        while (ligne != NULL) {
            previous = ligne;
            ligne = ligne->suivant; //on lit l'element suivant
            free(previous); //puis on supprime le precedent
        }
    }
    free(m.tab_lignes); //liberation de la liste des lignes
}





void main(){

    printf("Combien de matrices voulez-vous traiter ?\n");
    int nb=0,nb_max;
    scanf("%d",&nb_max);
    matrice_creuse *matrices=malloc(nb_max*sizeof(matrice_creuse));

    int continuer=1, reponse;
    while(continuer){
        printf("Que voulez-vous faire ?\n1. Remplir une matrice\n2. Afficher une matrice sous forme de tableau\n3. Afficher une matrice sous forme de liste\n4. Donner la valeur d'un élément d'une matrice\n5. Affecter une valeur à un élément d'une matrice\n6. Additionner deux matrices\n7. Calculer le gain d'espace pour une matrice\n8. Quitter\n\n");
        scanf("%d",&reponse);
        printf("\n");

        switch(reponse){
            case 1:
                if(nb<nb_max){
                    int nb_lignes,nb_colonnes;
                    printf("Nombre de lignes : ");
                    scanf("%d",&nb_lignes);
                    printf("Nombre de colonnes : ");
                    scanf("%d",&nb_colonnes);
                    remplirMatrice(&(matrices[nb]),nb_lignes,nb_colonnes);
                    nb+=1;
                    printf("\n");
                }
                else printf("Nombre maximum de matrices atteint\n\n");
                break;

            case 2:
                if(nb==0) printf("Vous n'avez aucune matrice à afficher.\n\n");
                else{
                    int i;
                    if(nb==1) i=0;
                    else{
                        printf("Vous avez %d matrices, laquelle voulez-vous afficher ?\n",nb);
                        scanf("%d",&i);
                        printf("\n");
                    }
                    afficherMatrice(matrices[i]);
                    printf("\n");
                }
                break;

            case 3:
                if(nb==0) printf("Vous n'avez aucune matrice à afficher.\n\n");
                else{
                    int i;
                    if(nb==1) i=0;
                    else{
                        printf("Vous avez %d matrices, laquelle voulez-vous afficher ?\n",nb);
                        scanf("%d",&i);
                        printf("\n");
                    }
                    afficherMatriceListes(matrices[i]);
                    printf("\n");
                }
                break;

            case 4:
                if(nb==0) printf("Vous n'avez aucune matrice à afficher.\n\n");
                else{
                    int i,ligne,colonne;
                    if(nb==1) i=0;
                    else{
                        printf("Vous avez %d matrices, laquelle voulez-vous afficher ?\n",nb);
                        scanf("%d",&i);
                    }
                    matrice_creuse m=matrices[i];
                    printf("La matrice contient %d lignes, laquelle voulez-vous afficher ?\n",m.Nlignes);
                    scanf("%d",&ligne);
                    printf("La matrice contient %d colonnes, laquelle voulez-vous afficher ?\n",m.Ncolonnes);
                    scanf("%d",&colonne);
                    printf("La valeur est %d\n\n",rechercherValeur(m,ligne,colonne));
                }
                break;

            case 5:
                if(nb==0) printf("Vous n'avez aucune matrice à modifier.\n\n");
                else{
                    int i,ligne,colonne,val;
                    if(nb==1) i=0;
                    else{
                        printf("Vous avez %d matrices, laquelle voulez-vous modifier ?\n",nb);
                        scanf("%d",&i);
                    }
                    matrice_creuse m=matrices[i];
                    printf("La matrice contient %d lignes, laquelle voulez-vous modifier ?\n",m.Nlignes);
                    scanf("%d",&ligne);
                    printf("La matrice contient %d colonnes, laquelle voulez-vous modifier ?\n",m.Ncolonnes);
                    scanf("%d",&colonne);
                    printf("Entrez une valeur : ");
                    scanf("%d",&val);
                    affecterValeur(m,ligne,colonne,val);
                    printf("\n");
                }
                break;

            case 6:
                if(nb<2) printf("Vous n'avez pas 2 matrices à additionner.\n\n");
                else{
                    int i;
                    printf("Vous avez %d matrices, quelle est la première matrice à additionner ?\n",nb);
                    scanf("%d",&i);
                    matrice_creuse m1=matrices[i];
                    printf("Quelle est la deuxième matrice à additionner ?\n");
                    scanf("%d",&i);
                    matrice_creuse m2=matrices[i];
                    additionerMatrices(m1,m2);
                    printf("\n");
                }
                break;

            case 7:
                if(nb==0) printf("Vous n'avez aucune matrice enregistrée.\n\n");
                else{
                    int i,ligne,colonne,val;
                    if(nb==1) i=0;
                    else{
                        printf("Vous avez %d matrices, pour laquelle voulez-vous connaitre le gain en espace ?\n",nb);
                        scanf("%d",&i);
                    }
                    printf("Cette représentation permet de gagner %d octets.\n\n",nombreOctetsGagnes(matrices[i]));
                }
                break;

            case 8:{
                int i;
                for(i=0;i<nb;i++) supprimerMatrice(matrices[i]);
                free(matrices);
                continuer=0;
                break;
            }
        }
    }

}
