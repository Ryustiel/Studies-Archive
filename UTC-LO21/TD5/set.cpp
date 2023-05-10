#include "set.h"
#include<cstdlib>

namespace Set {
	
	std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::mauve, Couleur::vert };
	std::initializer_list<Nombre> Nombres = { Nombre::un, Nombre::deux, Nombre::trois };
	std::initializer_list<Forme> Formes = { Forme::ovale, Forme::vague, Forme::losange };
	std::initializer_list<Remplissage> Remplissages = { Remplissage::plein, Remplissage::vide, Remplissage::hachure };

	string toString(Couleur c) {
		switch (c) { 
		case Couleur::rouge: return "R";
		case Couleur::mauve: return "M";
		case Couleur::vert: return "V";
		default: throw SetException("Couleur inconnue");
		}
	}

	string toString(Nombre v) {
		switch (v) {
		case Nombre::un: return "1";
		case Nombre::deux: return "2";
		case Nombre::trois: return "3";
		default: throw SetException("Nombre inconnue");
		}
	}

	string toString(Forme f) {
		switch (f) {
		case Forme::ovale: return "O";
		case Forme::vague: return "~";
		case Forme::losange: return "\004";
		default: throw SetException("Forme inconnue");
		}
	}

	string toString(Remplissage r) {
		switch (r) {
		case Remplissage::plein: return "P";
		case Remplissage::vide: return "_";
		case Remplissage::hachure: return "H";
		default: throw SetException("Remplissage inconnu");
		}
	}

	std::ostream& operator<<(std::ostream& f, Couleur c) { f << toString(c); return f; }
	std::ostream& operator<<(std::ostream& f, Nombre v) {	f << toString(v); return f; }
	std::ostream& operator<<(std::ostream& f, Forme x) { f << toString(x);  return f; }
	std::ostream& operator<<(std::ostream& f, Remplissage r) { f << toString(r); return f; }

	std::ostream& operator<<(std::ostream& os, const Combinaison& c) {
		os << "[" << c.getCarte1() << "," << c.getCarte2() << "," << c.getCarte3() << "]";
		return os;
	}

	void printCouleurs(std::ostream& f) {
		for (auto c : Couleurs) f << c << " ";
		f << "\n";
	}

	void printNombres(std::ostream& f) {
		for (auto v : Nombres) f << v << " ";
		f << "\n";
	}

	void printFormes(std::ostream& f) {
		for (auto x : Formes) f << x << " ";
		f << "\n";
	}

	void printRemplissages(std::ostream& f) {
		for (auto r : Remplissages) f << r << " ";
		f << "\n";
	}

	std::ostream& operator<<(std::ostream& f, const Carte& c) {
		f << "(" << c.getCouleur() << "," << c.getNombre() << ","
			<< c.getForme() << "," << c.getRemplissage() << ")";
		return f;
	}

	Jeu::Jeu(){
		size_t i = 0;
		for (auto c : Couleurs)
			for (auto v : Nombres)
				for (auto x : Formes)
					for (auto r : Remplissages)
						cartes[i++] = new Carte(c, v, x, r);
	}
	
	const Carte& Jeu::getCarte(size_t i) const{
		if (i >= getNbCartes()) throw SetException("carte inexistante");
		return *cartes[i];
	}
	
	Jeu::~Jeu(){
		for (size_t i = 0; i < getNbCartes(); i++) delete cartes[i];
	}

	Pioche::Pioche(const Jeu& j):
		cartes(new const Carte*[j.getNbCartes()]),
		nb(j.getNbCartes()){
		for (size_t i = 0; i < nb; i++) cartes[i] = &j.getCarte(i);
	}

	const Carte& Pioche::piocher(){
		if (estVide()) throw SetException("piocher dans une pioche vide");
		size_t x = rand() % nb;
		const Carte& c = *cartes[x]; // creation d'une ref sur la carte piochee
		cartes[x] = cartes[--nb]; // deplacement de la derniere carte 
							// a l'emplacement de l acrte piochee		
		return c;
	}
	
	Pioche::~Pioche(){
		delete[] cartes; // desallocation du tableau de pointeurs
	}

	Plateau::Plateau():cartes(new const Carte*[12]), 
		nbMax(12), nb(0) {
	}

	void Plateau::agrandirTableau(size_t t) {
		if (t <= nbMax) return;
		// allocation nouveau tableau
		auto nouveau_tab = new const Carte * [t];
		// recopie des donnees du tableau initial
		for (size_t i = 0; i < nb; i++) 
			nouveau_tab[i] = cartes[i];
		auto old = cartes;
		// mise a jour des attributs
		cartes = nouveau_tab;
		nbMax = t;
		// destruction ancien tableau
		delete[] old;
	}

	void Plateau::ajouterCarte(const Carte& c) {
		if (nb == nbMax) agrandirTableau((nb + 1)*2);
		cartes[nb++] = &c;
	}

	void Plateau::retirerCarte(const Carte& c) {
		size_t i = 0;
		while (i < nb && cartes[i] != &c) i++;
		if (i == nb) throw SetException("carte inexistante du plateau");
		cartes[i] = cartes[--nb];
	}

	Plateau::~Plateau() {
		delete[] cartes;
	}

	Plateau::Plateau(const Plateau& p): 
		cartes(new const Carte* [p.nb]),
		nbMax(p.nb),nb(p.nb){
		// recopie des adresses
		for(size_t i=0; i<nb; i++) cartes[i]=p.cartes[i];
	}
	
	Plateau& Plateau::operator=(const Plateau& p) {
		if (this != &p) { // on se protege de l'auto-affectation
			if (nbMax < p.nb) agrandirTableau(p.nb);
			for (size_t i = 0; i < p.nb; i++) 
				cartes[i] = p.cartes[i];
			nb = p.nb;
		}
		return *this;
	}
		

	bool Combinaison::estUnSet() const {
		bool c =(c1->getCouleur() == c2->getCouleur() && c1->getCouleur() == c3->getCouleur() && c3->getCouleur() == c2->getCouleur());
		return c;
	}
	

	void Controleur::distribuer() {
		if (plateau.getNbCartes() < 12) {
			while (!pioche->estVide() &&
				plateau.getNbCartes() < 12)
				plateau.ajouterCarte(pioche->piocher());
		}
		else if (!pioche->estVide()) {
			plateau.ajouterCarte(pioche->piocher());
		}
	}

	void afficherCartes(){
		for(Jeu::Iterator it = Jeu::getInstance().getIterator();!it.isDone();it.next())
			std::cout<<it.currentItem()<<"\n";
	}

	void afficherCartes(Plateau& p) {
		for(Plateau::const_iterator it = p.begin(); it != p.end(); ++it) {
			std::cout << *it << "\n";
		}
	}

}