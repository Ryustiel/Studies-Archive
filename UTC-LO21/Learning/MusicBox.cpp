#include "MusicBox.h"
#include <iostream>

std::string Note::noms[12] = {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};

Synthetiseur::~Synthetiseur() {
    // suppression du tableau
    for (size_t i = 0; i < 144; i++) {
        if (Synthetiseur::notes[i] != nullptr) {
            delete Synthetiseur::notes[i]; // freeing pointed objects (have been generated by this object)
        }
        // le destructeur customise va se faire appeler tout seul
    }
}

Note& Synthetiseur::getNote(unsigned int h, unsigned int o) {
    if (h >= 12 || o >= 12) {
        throw MusicException("Invalid note value (Synthetiseur::getNote)");
    }
    int i = o * 11 + h;
    if (Synthetiseur::notes[i] == nullptr) {
        Note* note = new Note(h, o); // cree un objet note
        Synthetiseur::notes[i] = note;
    }
    return *(Synthetiseur::notes[i]);
}

float Note::getFrequence() const {
    float exponant = (octave * 12 + hauteur) / 12;
    return 32.7 + exponant; //* pow(2, exponant);
}

std::string Note::getNom() const {
    return noms[hauteur];
}

void Accord::ajouterNote(Note* n) {
    if (nb <= 7) {
        notes[nb++] = n;
    }
    else {
        throw MusicException("trop de notes dans l'accord");
    }
}

void Mesure::agrandirTab() {
    if (nb % 3 != 0) {nb++; return;}
    // allocation nouveau tableau
    auto nouveau_tab = new const Accord * [nb + 3]; // pointeur sur tab
    // recopie des donnees du tableau initial
    for (size_t i = 0; i < nb; i++) 
        nouveau_tab[i] = accords[i];
    auto old = accords; // reference
    // mise a jour des attributs
    accords = nouveau_tab;
    // destruction ancien tableau
    delete[] old;
    nb++;
}

void Mesure::ajouterAccord(const Accord* accord) {
    agrandirTab();
    accords[nb] = accord;
}

void Morceau::expand(size_t n) {
    if (size < n) {
        size = 1 + size * 2;
        auto new_tab = new Mesure[size];
        for (int i = 0; i < nb-1; i++) { // copie
            new_tab[i] = mesures[i];
        }
        old = mesures;
        mesures = new_tab;
        delete[] old;
    }
}

void Morceau::ajouterMesure(Mesure& m) {
    expand(nb++);
    mesures[nb] = m;
}

void Morceau::play() {
    for (int i = 0; i < nb; i++) {
        mesures[i].play();
    }
}

void Mesure::play() {
    Synthetiseur synth = Synthetiseur::getSynthetiseur();
    for (int i = 0; i < nb; i++) {
        Accord* acc = accords[i];
        synth.play(a-> ...)
    }
}