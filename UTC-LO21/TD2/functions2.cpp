#include <string>
#include <stdio.h>
#include <iostream>

struct compte {
    std::string id;
    int solde;
};

int& operation(compte* t, const std::string& c) {
    size_t i = 0;
    while (t[i].id != c) {i++;}
    return t[i].solde; // il suffit de renvoyer ca
}

void essai_comptes(){
        compte tab[4]={ {"courant", 0},{"codevi", 1500 },{"epargne", 200 }, { "cel", 300 } };
        operation(tab,"courant") = 100;
        operation(tab,"codevi") += 100;
        operation(tab,"cel") -= 50;
        for(int i=0; i<4; i++) std::cout<<tab[i].id<<" : "<<tab[i].solde<<"\n";
    }

/*
t c'est un tableau de compte.
t[i] est un element du tableau
donc t[i] est un objet compte comme indiqué sur compte* l'identificateur de la variable
donc operation renvoie une reference sur la valeur qu'on veut
*/