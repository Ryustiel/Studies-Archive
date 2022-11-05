#include<stdio.h>

#define TABSIZE 20;
#define STRLEN 60;

typedef struct tableau {
    int ROWS;
    int COLS;
    int ncase; // nombre de cases non vides
    int **pointer; // 
};

typedef struct menu {
    struct tableau tab; // tableau de strings
    int n; // nombre d'items du menu
};

struct tableau create_table(int rows, int columns) {
    struct tableau tab;
    tab.ROWS = rows; tab.COLS = columns; tab.ncase=0;
    tab.pointer = malloc(sizeof(int)*rows);
    for (int i = 0; i < columns; i++) {tab.pointer[i] = malloc(sizeof(int)*columns);
    return tab;
}

void empty(struct tableau tab) {
    for (int i = 0; i < tab.rows; i++) {
        for (int j = 0; j < tab.columns; j++) {free(tab.pointer[i][j]);}
    }
}

void set(struct tableau *tab, int target[tab.rows][tab.columns]) {
    for (int i = 0; i < tab.rows; i++) {
        for (int j = 0; j < tab.cols; j++) {
            tab.pointer[i][j] = target[i][j];
        }
    }
}

int detter(struct tableau tab, int topleft[2], int size) {
    if (tab.rows != tab.cols || size > tab.rows) {return -1;}
    if (size == 1) {return 1;}
    int k = 0;
    for (int i = topleft[0]; i < topleft[0]+size; i++;) {
        k += tab[i][0] * detter(tab, newtopleft, size-1);
    }
}

void main() {
    struct tableau table = create_table(4, 4);
    
}

