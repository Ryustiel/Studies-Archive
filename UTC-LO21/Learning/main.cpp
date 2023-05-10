#include "MusicBox.h"
#include "MusicBox.cpp"
#include <iostream>

int main() {
    Synthetiseur& s = Synthetiseur::getSynthetiseur();
    std::cout << s.getNote(3, 1).getNom();
}