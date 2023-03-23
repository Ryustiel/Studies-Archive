#include <stdio.h>
#include<iostream>
#include<string>

void essai_alloc() {
    int* pt_int;
    double* pt_double;
    pt_int = (int*)malloc(sizeof(int));
    pt_double = (double*)malloc(sizeof(double)*100);
    std::free(pt_int);
}

void essai_alloc2() {
    int* pt_int;
    double* pt_double;
    pt_int = new int;
    pt_double = new double[100];
    delete pt_int;
    delete[] pt_double;
    free(pt_double);
}

struct essai {
    int n;
    float x;
    void raz();
};

void inverse(int& a, int& b) {
    auto tmp = a; a = b; b = tmp;
}

void essai::raz() {
    n = 0;
    x = 0;
    // sinon "this.x; this.n"
}

void raz(essai& e) {
    e.n = 0;
    e.x = 0;
}

void raz(essai* e) {
    e->n = 0;
    e->x = 0;
}

// EXO 16

struct personne {
    char string;
    unsigned int age;
    void raz();
    void afficher();
    void init_struct(const std::string& str, unsigned int age);
    void copy_struct(const personne& s);
    void copy_tab(personne* tabd, const personne* tabs, size_t n);
};


void personne::raz() {
    age = 0;
    nom[0] = '\0'; // ca marche
}

void personne::afficher() {
    std::cout << "\n" << nom << " : " << age;
}

void affiche_tab(const personnes* tab, size_t n) {
    for (size_t i=0; i<30; i++) {
        tab[i].afficher();
    }
}

void personne::init_struct(const std::string& str, unsigned int age) {
    /*
    personne* pers = new personne;
    size_t i = 0;
    while (nom[i] != '\0') { // ca marche
        pers->nom[i] = nom[i];
        i++;
    };
    nom[i] = '\0';
    pers->age = age;
    return pers;
    */
   nom = str;
   age = age;
}

void personne::copy_struct(const personne& s) {
    *this = s;
}

void personne::copy_tab(personne* tabd, const personne* tabs, size_t n) {
    for (size_t i = 0; i < n; i++) {
        tabd[i] = tabs[i];
    }
}
