#ifndef _SET_H
#define _SET_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
using namespace std;

namespace Set {
	// classe pour gerer les exceptions dans le set
	class SetException {
	public:
		SetException(const string& i) :info(i) {}
		string getInfo() const { return info; }
	private:
		string info;
	};

	// caracteristiques
	enum class Couleur { rouge, mauve, vert };
	enum class Nombre { un=1, deux=2, trois=3 };
	enum class Forme { ovale, vague, losange };
	enum class Remplissage { plein, vide, hachure };

	// conversion d'une caracteristique en string
	string toString(Couleur c);
	string toString(Nombre v);
	string toString(Forme f);
	string toString(Remplissage v);

	// ecriture d'une caracteristique sur un flux ostream
	ostream& operator<<(ostream& f, Couleur c);
	ostream& operator<<(ostream& f, Nombre v);
	ostream& operator<<(ostream& f, Forme x);
	ostream& operator<<(ostream& f, Remplissage r);

	// listes contenant les valeurs possibles pour chacune des caracteristiques
	extern std::initializer_list<Couleur> Couleurs;
	extern std::initializer_list<Nombre> Nombres;
	extern std::initializer_list<Forme> Formes;
	extern std::initializer_list<Remplissage> Remplissages;

	// affichage des valeurs possibles pour chaque caracteristiques
	void printCouleurs(std::ostream& f = cout);
	void printNombres(std::ostream& f = cout);
	void printFormes(std::ostream& f = cout);
	void printRemplissages(std::ostream& f = cout);

	class Carte {
	public:
		Carte(Couleur c, Nombre n, Forme f, Remplissage r) :
			couleur(c), nombre(n), forme(f), remplissage(r) {}
		Couleur getCouleur() const { return couleur; }
		Nombre getNombre() const { return nombre; }
		Forme getForme() const { return forme; }
		Remplissage getRemplissage() const { return remplissage; }
		~Carte() = default;
		Carte(const Carte& c) = default;
		Carte& operator=(const Carte& c) = default;
	private:
		Couleur couleur;
		Nombre nombre;
		Forme forme;
		Remplissage remplissage;
	};

	std::ostream& operator<<(std::ostream& f, const Carte& c);

	class Jeu { // <<singleton>> <<iterator>>
		public:
			class Iterator {
				public:
					Iterator() = default;
					const Carte currentItem() const { return *(Jeu::getInstance().cartes[i]); }
					void next() { i += 1; }
					bool isDone() const { return i >= Jeu::getInstance().getNbCartes(); }
			
				private:
					unsigned int i=0;
			};
			static Jeu& getInstance() { static Jeu newInstance; return newInstance; }
			
			// new returns a pointer !
			Iterator getIterator() { return Iterator(); } // getInstance() <= 
			size_t getNbCartes() const { return 81; }
			const Carte& getCarte(size_t i) const;
			// desactivation du costructeur de recopie et de l'affectation
			Jeu(const Jeu& j) = delete;
			Jeu& operator=(const Jeu& j) = delete;
		private:
			// interdiction de la construction/destruction
			// aux utilisateurs
			Jeu();
			~Jeu();
			const Carte* cartes[81]; // tableau de pointeurs const automatique
	};

	// singleton via handler
	/*

	# set.h

	class Jeu {
		private:
			class Handler: {
				...
			};
	}

	# set.cpp
	
	const Jeu& Jeu::getInstance() {
		if (handler.instance == nullptr) {
			handler.instance = new Jeu;
		}
		return *handler.instance;
	}

	void Jeu::libereInstance() {
		delete handler.instance;
		handler.instance = nullptr;
	}
	*/

	class Pioche {
	public:
		explicit Pioche( const Jeu& j); // se construit a partir du jeu...
		const Carte& piocher();
		~Pioche();
		Pioche(const Pioche&) = delete;
		Pioche& operator=(const Pioche&) = delete;
		size_t getNbCartes() const { return nb; }
		bool estVide() const { return nb == 0; }
	private:
		const Carte** cartes=nullptr; // tableau de poiteurs const alloue dynamiquement
		size_t nb = 0;
	};

	class Plateau {
	public:
		class const_iterator { // parce que renvoie une reference const (sur operator*)
			public:
				const_iterator& operator++() { courant++; return *this; } // next
				const Carte& operator*() const { return **courant; }; // getValue
				bool operator!=(const_iterator it) const { return courant != it.courant; } // isDone?
			private:
				const Carte** courant; // adresse de la cellule courante
				// dnas le tableau de pointeurs de cartes
				const_iterator(const Carte** c): courant(c) {} // *(Carte*[])
				friend class Plateau;
		};
		const_iterator begin() const { return const_iterator(cartes); }
		const_iterator end() const { return const_iterator(cartes+nb); } // savoir quand ca se finit

		Plateau();
		void ajouterCarte(const Carte& c);
		void retirerCarte(const Carte& c);
		size_t getNbCartes() const { return nb; }
		~Plateau();
		Plateau(const Plateau& p);
		Plateau& operator=(const Plateau& p);
	private:
		void agrandirTableau(size_t t);
		const Carte** cartes = nullptr; // tableau de poiteurs const alloue dynamiquement
		size_t nbMax; // taille du tableau
		size_t nb = 0; // nb de cartes dans le tableau
	};

	class Combinaison {
		public: 
			~Combinaison() = default; // constructeur par defaut egalement valide
			Combinaison() = default;
			const Carte& getCarte1() const { return *c1; } // reference => retourner valeur pointee par le truc qui stocke une reference
			const Carte& getCarte2() const { return *c2; }
			const Carte& getCarte3() const { return *c3; }
			bool estUnSet() const;
		private: 
			const Carte* c1;
			const Carte* c2;
			const Carte* c3;
	};

	ostream& operator<<(ostream& os, const Combinaison& c);

	class Controleur {
		public: 
			Controleur() : jeu(&Jeu::getInstance()) { pioche = new Pioche(*jeu); }; // pioche = new Pioche(Jeu::getInstance());
			void distribuer(); // il reste a definir

			~Controleur() { delete pioche; }
			Controleur(const Controleur&) = delete;
			Controleur& operator=(const Controleur&) = delete; // = renvoie une adresse...
		private:
			Jeu* jeu=nullptr; // ordre d'initialisation des attributs
			Plateau plateau;
			Pioche* pioche=nullptr;
	};

}


#endif
