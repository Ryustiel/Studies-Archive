#include "fraction.h"
#include "fraction.cpp"
#include <iostream>

/*
int main() {
    MATH::Fraction f1(3, 4);
    MATH::Fraction f2(2, 4);

    MATH::Fraction f3 = f1 - f2; // operator-(f1, f2)
    // MATH::Fraction f4 = f1 + 3; // operator+(f1, Fraction(3)) <= si defini a l'exterieur
    // MATH::Fraction f5 = 3 + f1; // 3.operator+(f1) <= si defini comme objet de classe
    // ne fonctionne pas dans ce sens!

    f3.simplification();

    std::cout << f3.getNumerator();

    return 0;
}
*/

using namespace std;
using namespace MATH;

int main() {
    Fraction f1(1, 0);
    cout << f1;

    catch (FractionException e) {
        std::cout << e.getInfo() << "\n";
    }

    return 0;
}

/*

int main() {
    Fraction f1(3, 4);
    Fraction f2(1, 6);
    Fraction* pf3 = new Fraction(1, 2);
    cout << "ouverture d’un bloc\n";
    Fraction* pf6;
    {
        Fraction f4(3, 8);
        Fraction f5(4, 6);
        pf6 = new Fraction(1,3);
    }
    cout << "fin d’un bloc\n";
    cout << "debut d’une fonction\n";
    Fraction* pf7 = myFunction();
    cout << "fin d’une fonction\n";
    cout << "desallocations controlee par l’utilisateur :\n";
    delete pf6;
    delete pf7;
    return 0;
}

*/