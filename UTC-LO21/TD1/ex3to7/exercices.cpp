#include <stdio.h>

void exerciceA(){
    int r;
    const double PI = 3.14159; // typer les constantes
    double p, s;
    printf("donnez le rayon entier d’un cercle:");
    scanf("%d",&r);
    p=2*PI*r;
    s=PI*r*r;
    printf("le cercle de rayon %d ",r);
    printf("a un perimetre de %f et une surface de %f\n",p,s);
}

