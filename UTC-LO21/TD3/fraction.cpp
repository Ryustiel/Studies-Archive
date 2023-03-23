#include "fraction.h"
#include <iostream>

// à ajouter en tant méthode privée de la classe Fraction
void MATH::Fraction::simplification() { 
    // si le numerateur est 0, le denominateur prend la valeur 1
    if (numerator == 0) { denominator = 1; return; }
    /*un denominateur ne devrait pas être 0;si c’est le cas, on sort de la méthode*/
    if (denominator == 0)return;
    /*utilisation de l’algorithme d’Euclide pour trouver le Plus Grand CommunDenominateur (PGCD) entre le numerateur et le denominateur*/
    int a = numerator, b = denominator;
    // on ne travaille qu’avec des valeurs positives...
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (denominator == 1) return;
    while (a != b) {
        if ( a > b ) a = a - b;
        else b = b - a; 
    }
    // on divise le numerateur et le denominateur par le PGCD=a
    numerator /= a; 
    denominator /= a;
    // si le denominateur est négatif, on fait passer le signe - au denominateur
    if (denominator < 0) { 
        denominator = -denominator; 
        numerator = -numerator; 
    }
}



/*
MATH::Fraction MATH::somme(const Fraction& f1, const Fraction& f2) {
    return Fraction(
        f1.getNumerateur() * f2.getDenominateur() +
        f2.getNumerateur() * f1.getDenominator(), 
        f1.getDenominator() * f2.getDenominator()
        );
}
===> La methode ne fait pas partie de la classe */

MATH::Fraction MATH::Fraction::somme(const Fraction& f2) {
    return Fraction(
        this->numerator * f2.getDenominator() +
        f2.getNumerator() * this->denominator, 
        this->denominator * f2.getDenominator()
        );
}

MATH::Fraction MATH::Fraction::operator-(const Fraction& f2) {
    return Fraction(
        this->numerator * f2.getDenominator() -
        f2.getNumerator() * this->denominator, 
        this->denominator * f2.getDenominator()
        );
}

void MATH::Fraction::setFraction(int n, int d) {
    if (d == 0) throw "erreur";
    numerator = n; denominator = d;
}

MATH::Fraction MATH::Fraction::operator++() { // prefixe
    numerator += denominator;
    simplification();
    return *this; // simuler le fonctionnement de ++ postfixe et prefixe
}

MATH::Fraction MATH::Fraction::operator++(int) { // postfixe
    Fraction old(numerator, denominator); // old appelle l'ancienne definition de l'operateur !
    numerator += denominator;
    simplification();
    return old; // on aurait tres bien pu ne rien renvoyer, le type des operateurs est libre
}

std::ostream& operator<<(std::ostream& f, const MATH::Fraction& frac) {
    f << frac.getNumerator();
    if (frac.getDenominator() != 1)
        f << " / " << frac.getDenominator();
    return f;
}

MATH::Fraction* myFunction() {
    MATH::Fraction fx(7,8);
    MATH::Fraction* pfy = new MATH::Fraction(2, 3);
    return pfy;
}

