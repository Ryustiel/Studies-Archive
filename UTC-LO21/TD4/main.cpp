#include "set.h"
#include "set.cpp"
using namespace Set;

int main() {
	try {

		printCouleurs();
		printNombres();
		printFormes();
		printRemplissages();
	}
	catch (SetException& e) {
		std::cout << e.getInfo() << "\n";
	}
	
	Carte c(Couleur::rouge, Nombre::deux, Forme::vague, Remplissage::hachure);

	std::cout << c;

	//Carte tab[5]; // pas de constructeur sans argument ou de constructeur carte
	//Carte* tab[5]; // va fonctionner pck pas besoin de les initialiser, on peut toujours construire le tableau de pointeurs et construire les objets au fur et a mesure

	Jeu j;
	std::cout << j.getNbCartes();


	system("pause");
	return 0;
}