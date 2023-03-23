#include<iostream>
#include<string>
#include "fonction.h"

using namespace std;

void bonjour() {
    cout << "Entrez votre prenom :";
    string prenom;
    cin >> prenom;
    cout << "Bonjour " << prenom << "\n";
}