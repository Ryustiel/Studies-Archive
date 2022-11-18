#include<stdio.h>

int estPremier(int nombre) {
    for (int i=2; i<nombre; i++) {
        if ((nombre%i) == 0) {
            return 0; // divisible par ce nombre
        }
    };
    return 1; // pas divisible par aucun entier entre 1 et soi meme exclus
}

int main() {
    printf("blah");
    printf("\n== %d numbers ==\n", estPremier(36));
    printf("bluh");   
    return 1;
}