#if !defined(_EVENEMENT_H)
#define _EVENEMENT_H
#include <iostream>
#include <string>
#include "timing.h"
namespace TIME{
    class Evt1j {
    private:
        Date date;
        std::string sujet;
    public:
        Evt1j(const Date& d, const std::string& s):date(d),sujet(s){ std::cout << "Construction Evt1j" << this << "\n"; }
        const std::string& getDescription() const { return sujet; }
        const Date& getDate() const { return date; }
        void afficher(std::ostream& f= std::cout) const {
        f<<"***** Evt ********"<<"\n"<<"Date="<<date<<" sujet="<<sujet<<"\n";
        }
        ~Evt1j() { std::cout << "Destruction Evt1j" << this << "\n"; }
    };
    
    classEvtjDur : public Evt1j {
        private:
            Horaire horaire;
            Duree duree;
        public:
            Evt1jDur(const Date& d, const std::string& s, const Horaire& h, const Duree& d): 
                Evt1j(d, s), // appel au constructeur de la classe de base
                horaire(h),
                duree(dur) 
                { std::cout << "Construction Evt1jDur" << this << "\n"; } // c'est ça la partie la plus dure : faire des appels à la classe de base
            const Horaire& getHoraire() const { return horaire; }
            const Duree& getDuree() const { return duree; }
            void affiche(std::ostream& f = cout) const { // on n'a pas accès à la partie privée de la classe de base. (utiliser #protected)
                Evt1j::afficher(f);
                f << "Horaire=" << horaire << "Duree=" << duree << "\n";
                return f;
                };
            ~Evt1jDur() { std::cout << "Destruction Evt1jDur" << this << "\n"; }
    };

    class Rdv : public Evr1jDur {
        private:
            std::string personnes;
            std::string lieu;
        public:
            Rdv(const Date& d, const std::string& s,
            const Horaire& h, const Duree& dur,
            const std::string& p, const std::string& l) : 
            Evt1jDur(d, s, h, dur), personnes(p), lieu(l) 
            { std::cout << "Construction Rdv" << this << "\n"; }

            const std::string& getPersonnes() const { return personnes; }
            const std::string& getLieu() const { return lieu; }
            void afficher(std::ostream& f = cout) const {
                Evt1jDur::afficher(f);
                f << "Personnes=" << personnes << "Lieu=" << lieu << "\n";
            }
            ~Rdv() { std::cout << "Destruction Rdv" << this << "\n"; }
    }
}
#endif
