#include<stdio.h>

int main()
{
    int tab[3][4]; // n elements dans chaque trucs => max indice = (n-1)

    for (int* j = tab, max = j+(sizeof(tab)/sizeof(int)); j < max; j++) {*j = 4;} 
    // tab est l'addresse du zero, les autres addresses se decomptent a partir de la principale / du zero
    
    printf("\n%d %d %d %d %d", sizeof(tab)/sizeof(int), tab[0][0], tab[0][12], tab[2][3], tab[0][11]);

    int num = 12;
    for (int* j = tab, max = j+(sizeof(tab)/sizeof(int)); j < max; j++) {*j = num; num++;} 

    printf("\n%d %d %d %d %d", sizeof(tab)/sizeof(int), tab[0][0], tab[0][12], tab[2][3], tab[0][11]);

    return 0;
}