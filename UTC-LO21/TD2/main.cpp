#pragma once

#include <stdio.h>
#include<iostream>
#include<string>

#include "test.cpp"

int main() {
    int blah = 22;
    int bluh = 4;

    inverse(blah, bluh);
    std::cout << blah << " " << bluh;

    struct essai e;
    e.n = 28;
    struct essai* d = &e;
    
    e.raz();
    std::cout << "\n\n" << d->n;

    // exos suivants

    std::cout << "\n";
    struct personne p;
    p.init_struct("blah", 5000);
    p.raz();
    p.afficher();

    return 0;
}