#pragma once
#include <string>

class MusicException {
    public:
        MusicException(const std::string& message) : info(message) {}
        std::string getInfo() const { return info; }
    private:
        std::string info;
};

class Synthetiseur;

class Note {
    public:
        float getFrequence() const;
        std::string getNom() const;

    private:
        friend Synthetiseur;
        unsigned int hauteur;
        unsigned int octave;
        Note(unsigned int h, unsigned int o) : hauteur(h), octave(o) {}; // inline
        ~Note() = default; // rien de special a definir
        static std::string noms[12];
};

class Synthetiseur {
    public: 
        // singleton
        Synthetiseur(const Synthetiseur&) = delete; // suppression de la copie
        void operator=(const Synthetiseur&) = delete;
        // obtention de Note
        Note& getNote(unsigned int h, unsigned int o); // non const
        static Synthetiseur& getSynthetiseur() {
            static Synthetiseur instance; // si l'instance existe deja on dit nonono
            return instance;
        } 
    private:
        Note* notes[144] = {};
        Synthetiseur() = default; // redefinition dans la source
        ~Synthetiseur();
};

class Accord {
    public: 
        void ajouterNote(Note* n);
        Accord() = default;
    private:
        unsigned int nb=0;
        Note* notes[7];
};

class Mesure {
    public:
        void ajouterAccord(Accord* acc);
        Mesure(unsigned int n, unsigned int d): numerator(n), denominator(d) {}
    private:
        unsigned int nb;
        Accord** accords = nullptr;
        void agrandirTab();
};

class Morceau {
    public:
        void ajouterMesure(Mesure& m);
        Morceau() = default;
        Morceau(Morceau& m) = delete;
        Morceau& operator=(Morceau& m) = delete;
    private:
        unsigned int nb;
        unsigned int size;
        Mesure* mesures = nullptr;
        void expand();
}

