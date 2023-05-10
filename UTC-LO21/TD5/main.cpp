#include "set.h"
#include "set.cpp"
using namespace Set;

int main() {
	try {
		Carte c1(Couleur::rouge, Nombre::deux,
		Forme::losange, Remplissage::hachure);
		std::cout << c1 << "\n";

		//Carte c;
		//Carte tab[5];

		// Carte* pt;
		// Carte* tab[5];

		/*printCouleurs();
		printNombres();
		printFormes();
		printRemplissages();*/
	}
	catch (SetException& e) {
		std::cout << e.getInfo() << "\n";
	}

	// afficherCartes();
		


	system("pause");
	return 0;
}