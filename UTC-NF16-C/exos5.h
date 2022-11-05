le fichier main.c contient le main, module.c contient des fonctions, et module.h contient les declarations de fonctions
l'interet des fichiers d'entete ".h", c'est qu'ils copient colle les fonctions, ce qui permet de declarer les fonctions globalement, 
sinon c'est limite au fichier -- permet les include

doit contenir les declarations (sans code) des fonctions du fichier c du meme nom pour les inclure
ce fichier doit etre inclu dans d'autres modules pour import, mais pas le fichier c associe
il peut contenir aussi des struct et des typedef 
c'est definitivement une maniere de structurer les projets