#ifndef _SET_H
#define _SET_H

#include <iostream>
#include <string>
#include <ostream>
#include <initializer_list>
#include <array>
#include <cstdlib>
using namespace std;

namespace Set {
	// classe pour g�rer les exceptions dans le set
	class SetException {
	public:
		SetException(const string& i) :info(i) {}
		string getInfo() const { return info; }
	private:
		string info;
	};

	// caract�ristiques
	enum class Couleur { rouge, mauve, vert };
	enum class Nombre { un=1, deux=2, trois=3 };
	enum class Forme { ovale, vague, losange };
	enum class Remplissage { plein, vide, hachure };

	// conversion d'une caract�ristique en string
	string toString(Couleur c);
	string toString(Nombre v);
	string toString(Forme f);
	string toString(Remplissage v);

	// �criture d'une caract�ristique sur un flux ostream
	ostream& operator<<(ostream& f, Couleur c);
	ostream& operator<<(ostream& f, Nombre v);
	ostream& operator<<(ostream& f, Forme x);
	ostream& operator<<(ostream& f, Remplissage r);

	// listes contenant les valeurs possibles pour chacune des caract�ristiques
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;
	extern std::initializer_list<Forme> Formes;
	extern std::initializer_list<Remplissage> Remplissages;

	// affichage des valeurs possibles pour chaque caract�ristiques
	void printCouleurs(std::ostream& f = cout);
	void printNombres(std::ostream& f = cout);
	void printFormes(std::ostream& f = cout);
	void printRemplissages(std::ostream& f = cout);

	class Carte {
		public:
			Carte(Couleur c, Nombre n, Forme f, Remplissage r) :
				couleur(c), nombre(n), forme(f), remplissage(r) {}
			Couleur getCouleur() const { return couleur; } // testé au médian : est ce qu'on sait faire des méthodes const
			Nombre getNombre() const { return nombre; }	
			Forme getForme() const { return forme; }
			Remplissage getRemplissage() const { return remplissage; }
			~Carte() = default; // maniere de le dire explicitement
			Carte(const Carte& c) = default;
			Carte& operator=(const Carte& c) = default;
		private:
			Couleur couleur;
			Nombre nombre;
			Forme forme;
			Remplissage remplissage;
	};

	class Jeu {
		private:
			const Carte* cartes[81]; // le constructeur doit initialiser les cartes
		public:
			Jeu();
			size_t getNbCartes() const { return sizeof(cartes) / sizeof(cartes[0]); }
			const Carte& getCarte(size_t i) const;
			~Jeu();
			Jeu(const Jeu& j) = delete; // si on essaie de recopier le compilateur va refuser
			Jeu& operator=(const Jeu& j) = delete;
	};

	class Pioche {
		public:
			Pioche(const Jeu& j);
			const Carte& piocher();
			size_t getNbCartes() const { return nb; }
			bool estVide() const { return nb == 0; }
		private:
			const Carte** cartes=nullptr; // tableau de pointeurs const
			size_t nb = 0; // se demander, de quoi on est responsable dans la classe : là on est responsable du tableau alloué dynamiquement
	};

	class Plateau {
		public: 
			Plateau();
			~Plateau();
			void ajouterCarte(const Carte& c);
			void retirerCarte(const Carte& c);
			Plateau(const Plateau& p); // duplicateur
			Plateau& operator=(const Plateau& p);
		private:
			void agrandirTableau(size_t t); // controle l'extension de tableau
			const Carte** cartes = nullptr; // tableau de pointeurs
			size_t nb = 0;
			size_t nbMax; // taille du tableau
	};
}


#endif