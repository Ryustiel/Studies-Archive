#include <iostream>
#include "fonction.h"

void french::bonjour() 
{
        std::cout << "nichao\n";
}

namespace english
{
    void bonjour() 
    {
        std::cout << "hello\n";
    }
}

int fct(int x) { std::cout << "1:" << x << "\n"; return 0; }
int fct(float y) { std::cout << "2:" << y << "\n"; return 0; }
int fct(int x, float y) { std::cout << "3:" << x << y << "\n"; return 0; }
float fct(float x, int y) { std::cout << "4:" << x << y << "\n"; return 3.14; }

void exercice_surcharge() {
    int i = 3, j = 15;
    float x = 3.14159, y = 1.414;
    char c = 'A';
    double z = 3.14159265;
    fct(i); // appel 1 (fct1)
    fct(x); // appel 2 (fct2)
    fct(i, y); // appel 3 (fct3)
    fct(x, j); // appel 4 (fct4)
    fct(c); // appel 5 (fct1) <- conversion implicite char vers int; explicite : (int)c
    fct(static_cast<int>(c)) // statique : au moment de la compilation, ajouter
    // meilleure facon de convertir, mais il y en a d'autre
    //fct(i, j); // appel 6 <- convertir une des deux variables en float fct(static_cast<float>(i), j)
    //fct(i, c); // appel 7 ... pareil
    fct(i, z); // appel 8 (fct3)
    //fct(z, z); // appel 9
}