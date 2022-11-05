#include<stdio.h>

#define TAB_SIZE 20
#define STR_SIZE 60


struct Menu {
    char tab[TAB_SIZE][STR_SIZE];
    int n;
};

int max_length(struct Menu m) {
    int max = strlen(m.tab[0]);
    int i;
    for(i=1; i<m.n; i++) {
        if (strlen(m.tab[i]) > max) {
            max = strlen(m.tab[i]);
        }
    }
    return max;
}

void affiche(struct Menu m) {
    int l = max_length(m);
    int i, j;
    for (i = 0; i < m.n; i++) {
        for (j = 0; j < (l-strlen(m.tab[i]))/2; j++) {
            printf(" ");
        }
        printf("%d : %s", i+1, m.tab[i]);
    }
}

int choix_menu(struct Menu m) {
    int i;
    char choice[STR_SIZE];
    do {
        system("clear");
        affiche(m);
        printf("Veuillez saisir un menu (Q ou q pour quitter)");
        fgets(choice, STR_SIZE, stdin);
        // scanf("%[^\n]%*c", choice); --- lis tous les caracteres jusqu'a \n et %*c lis le caractere mais ne le stocke pas

        for(i = 0; i < m.n; i++) {
            if(strcmp(m.tab[i], choice) == 0) {
                return choice;
            }
        }
    } while (1);
}



typedef struct tonneau {
    float d;
    float D;
    float L;
    char contenu[STR_SIZE];
};

// ou struct tonneau {}; typedef struct tonneau tonneau; -- ne marche pas a l'interieur si strucutre recursive car typedef pas encore effectif


void main() {
    
    struct Menu m;
    m.n = 3;
    strcpy(m.tab[0], "Poulet currish");
    strcpy(m.tab[1], "Explosion de canapes");
    strcpy(m.tab[2], "Blahgiblahgou");

    printf("%d", max_length(m));
}
