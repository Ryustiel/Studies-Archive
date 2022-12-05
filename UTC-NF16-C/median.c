#include<stdio.h>


typedef struct node {
    int value;
    struct node* next;
} node;

node* creer_node(int val) {
    node* n = malloc(sizeof(node));
    n->value = val;
    n->next = NULL;
    return n;
}

node* creer_liste(int* tab, int len) {
    node* n = creer_node(tab[0]);
    node* ptr = n;
    for (int i = 1; i < len; i++) {
        ptr->next = creer_node(tab[i]);
        ptr = ptr->next;
    }
    return n;
}

node* invert(node* n) {
    if (n->next == NULL) {
        node* head = creer_node(n->value);
        return head;
    }
    else {
        node* head = invert(n->next);
        node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = creer_node(n->value);
        // now n is at the end of invert
        return head;
    }
}

int main() {

    int tab[5] = {1, 2, 3, 4, 5};
    node* n = creer_liste(tab, 5);

    n = invert(n);

    node* ptr = n;
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }

    return 0;

}






int estPremier(int nombre) {
    for (int i=2; i<nombre; i++) {
        if ((nombre%i) == 0) {
            return 0; // divisible par ce nombre
        }
    };
    return 1; // pas divisible par aucun entier entre 1 et soi meme exclus
}

void matBinomial(int n, int M[10][11]) {
    M[n][0] = 1; // 1 parmi n
    if (n > 1) {
        matBinomial(n-1, M); // filling previous line
        for (int j = 1; j < n; j++) { // then using previous line
            M[n][j] = (int)M[n-1][j] + (int)M[n-1][j-1];
            //printf("%d %d", M[n-1][j], M[n-1][j-1]);
        }
    }
    M[n][n] = 1; // n parmi n
}

int main2() {

    int M [10][11];
    for (int i=0; i<10; i++) {
        for (int j=0; j<11; j++) {
            M[i][j] = 0;
        }
    }
    matBinomial(10, M);
    
    for (int i=0; i<=10; i++) {
        printf("\n");
        for (int j=0; j<=11; j++) {
            printf("%d ", M[i][j]);
        }
    }

    return 0;
}

