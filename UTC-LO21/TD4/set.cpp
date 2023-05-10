#include "set.h"

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
		f << "(" << c.getCouleur() << "," << c.getNombre() << "," << c.getForme() << "," << c.getRemplissage() << ")";
		f << "\n";
		return f;
	}

	const Carte& Jeu::getCarte(size_t i) const{
		if (i >= getNbCartes()) throw SetException("carte inexistante");
		return *cartes[i];
	}

	Jeu::Jeu() {
		/*const Couleur couleurs[3] = {Couleur::mauve, Couleur::rouge, Couleur::vert};
		const Nombre nombre[3] = {Nombre::un, Nombre::deux, Nombre::trois};
		const Forme forme[3] = {Forme::ovale, Forme::vague, Forme::losange};
		const Remplissage remplissage[3] = {Remplissage::plein, Remplissage::vide, Remplissage::hachure};

		int i = 0;
		for (int j = 0; j <= 2; j++) {
			for (int k = 0; k <= 2; k++) {
				for (int l = 0; l <= 2; l++) {
					for (int m = 0; m <= 2; m++) {
						cartes[i] = new Carte(...);
					}
				}
			}
		}*/

		size_t i = 0;
		for (auto c : Couleurs) 
			for (auto v : Nombres) 
				for (auto x : Formes) 
					for (auto r : Remplissages)
						cartes[i++] = new Carte(c, v, x, r);
	}

	Jeu::~Jeu() {
		for (size_t i = 0; i < getNbCartes(); i++) delete cartes[i];
	}

	Pioche::Pioche(const Jeu& j): 
		cartes(new const Carte*[j.getNbCartes()]), 
		nb(j.getNbCartes()) {
			for (size_t i = 0; i < nb; i++) cartes[i] = &j.getCarte(i);
		}

	const Carte& Pioche::piocher() {
		if (estVide()) throw SetException("piocher dans une pioche vide est impossible");
		size_t x = rand() % nb;
		auto c = *cartes[x]; // creation d'une ref sur la carte piochee
		cartes[x] = cartes[--nb]; // déplacement de la derniere carte à l'emplacement de la x carte
		return c;
	}

	Pioche::~Pioche() {
		delete[] cartes; // désallocation du tableau de pointeurs
	}

	Plateau::Plateau() : nbMax(12), new const Set::Carte*[12], nb(0) {}
	
	void Plateau::agrandirTableau(size_t t) { // non constructeur ni rien, doit etre typee
		if (t <= nbMax) return;
		// allocation nouveau tableau
		auto nouveau_tab = new const Set::Carte*[t];
		// recopie des données du tableau initial
		for (size_t i=0; i<nb; i++) nouveau_tab[i] = cartes[i];
		auto old = cartes; // conserver la reference
		// mise à jour des attributs
		cartes = nouveau_tab;
		nbMax = t;
		// destruction ancien tableau
		delete[] old;
	}
	Plateau::~Plateau(){
		delete[] cartes; // on veut juste desalouer le tableau de pointeurs
	};
	void Plateau::ajouterCarte(const Carte& c) {
		if (nb == nbMax) agrandirTableau((nb+1)*2); // garanti -- jouglet aurait tendance à 2*(nb+1), car l'agrandissement est couteux
		cartes[nb++] = &c; // insersion
	}
	void Plateau::retirerCarte(const Carte& c){
		size_t i = 0;
		while (i < nb && cartes[i] != &c) i++;
		if (i == nb) throw SetException("carte inexistante : la suppression est absurde");
		cartes[i] = cartes[--nb];
	};
	Plateau::Plateau(const Plateau& p) {
		Carte(new const Carte* [p.nb]), nbMax(p.nb), nb(p.nb) {
			// recopie des adresses
			for (size_t i=0; i<nb, i++) cartes[i]=p.cartes[i];
		} 
	}; // duplicateur
	Plateau& Plateau::operator=(const Plateau& p){
		if (this != &p) { // éviter l'auto affectation (pas très grave mais... un peu con)
			if (nbMax < p.nb) agrandirTableau(p.nb);
			for (size_t i=0; i < nb; i++) 
				cartes[i] = p.cartes[i];
			nb = p.nb;
		}
		return *this; // type : adresse
	};

}
