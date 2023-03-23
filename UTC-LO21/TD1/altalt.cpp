#include <stdio.h>

int main()
{
    double* pt0 = 0;
    double* pt1 = (double*)4096;
    double* pt2 = reinterpret_cast<double*>(4096); // seul moment du semestre ou on va l'utiliser

    printf("\n\n\noke\n\n\n");

    void* pt3 = pt1; // void truc universel
    pt1 = static_cast<double*>(pt3); // type indique explicitement, le compilateur laisse passer
    // pt1 = pt3 ne marchera pas, securite

    double d1 = 36;
    const double d2 = 36;
    double* pt4 = &d1;
    const double* pt5 = &d1;
    *pt4 = 2.1;
    // *pt5 = 2.1; // la donnee pointee par const double* (pointeur sur constante) can't be changed
    // pt4 = &d2; // on doit caster depuis constante
    pt4 = const_cast<double*>(&d2);
    // *pt4 = 42 on vient de modifier une constante, si on en arrive la le programme est mal foutu
    pt5 = &d2; // un pointeur sur const n'est pas constant, c'est juste la valeur ki e pas modifiable

    double* const pt6 = &d1; // ca c'est un pointeur constant, et vous devez l'initialiser
    *pt6 = 2.78; // va fonctionner : on modifie la donnee pointee
    // c'est un pointeur constant non const, on peut pas stocker l'adresse d'une constante

    // const double* const pt7 = &d1; // non car d1 n'est pas une constante !
    
    
}