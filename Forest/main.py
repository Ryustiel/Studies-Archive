import turtle #imports
from random import randint #generation aleatoire
t = turtle.Turtle() #turtle hors du main, pour eviter les overlap de noms

t.speed("fastest") #accelere le rendu graphique


#FONCTION FEUILLE

def feuille(h, i=3, s=0):
  """
  feuille(sqrt(2)*hauteur, nombre de sillons, decallage de depart)

  genere une feuille a l'aide du turtle.
  h est la longueur du premier cote de la feuille, 
  i est le nombre d'iterations restantes,
  s est le decallage vers l'avant de la nouvelle feuille. (affecter s n'impacte que la premiere execution de la fonction)
  """
  if (i <= 0) or (h<5): #condition d'arret, (h<5) limite la taille minimale d'une feuille pour eviter les bugs)
    return

  else:
    t.forward(s) #avance d'une certaine distance pour creer les rainures de la feuille a partir de ce qui etait auparavant leur base

    t.left(130) #construction de la moitie gauche de la feuille
    t.forward(h)
    t.right(150)
    t.forward((h*22)/10)

    t.backward((h*22)/10) #retour en arriere
    t.left(150)
    t.backward(h)
    t.right(130)

    t.left(-130) #construction de la moitie droite, identique a la moitie gauche, sauf que les rotations sont inversees
    t.forward(h)
    t.right(-150)
    t.forward((h*22)/10)

    t.backward((h*22)/10)
    t.left(-150)
    t.backward(h)
    t.right(-130)

    feuille((h*3)/4, i-1, h/3) #repete la fonction

    t.backward(s) #annule les decallages pour retrouver la position initiale du turtle


#FONCTION ARBRE

def arbre(hauteur, profondeur, epaisseur, couleur, angle, nb_branche):
  """
  arbre(hauteur, profondeur, epaisseur, (redValue, greenValue, blueValue), angle, nb_branche)

  genere un arbre avec les parametres indiques :
  - hauteur est un integer, la hauteur du tronc, divise par 2 pour chaque nouvelle ramification.
  - profondeur est un integer, le nombre maximal de branches ramifiees a partir du tronc
  - epaisseur est un integer, l'epaisseur du tronc, reduit de 1/3 a chaque nouvelle ramifiction
  - couleur est un tuple d'integer, la couleur du tronc au format (R, G, B), RGB 255 bits, qui sera ramene progressivement a (120, 205, 75)
  - angle est un integer, il correspond a l'angle entre deux branches
  - nb_branche est un integer, il correspond au nombre de branches par ramification, il ne peut pas etre superieur a 7.
  """

  #gestion des erreurs
  if (nb_branche > 7):
    raise ValueError("le nombre de branches doit etre inferieur a 7")
  for variable in [hauteur, profondeur, epaisseur, angle, nb_branche] :
    if (type(variable) != int):
      raise TypeError("un parametre, qui n'est pas couleur, n'est pas un integer alors qu'il devrait l'etre")
  if (type(couleur) != tuple):
    raise TypeError("couleur n'est pas un tuple")
  else:
    for i in range(3):
      if (type(couleur[i]) != int):
        raise TypeError("le tuple couleur ne comporte pas trois valeurs integer")

  #condition d'arret dont trace des branches extremes
  if (profondeur==0):
    t.width(epaisseur) 
    t.color(120, 205, 75) #ajuste parametre de couleur fixes pour la derniere branche (pour etre sur d'avoir du vert)

    t.forward(hauteur)

    t.width(epaisseur/3) #reduit la largeur du trait pour la feuille
    feuille(hauteur/2) #genere une "feuille"

    t.penup() #retourne au point de depart pour les fonctions de la pile, sans tracer de trait
    t.backward(hauteur)
    t.pendown()

  else:
    t.width(epaisseur) #ajuste epaisseur et couleur avec les parametres eventuellement heritee de l'execution de la recursion precedente
    t.color(couleur)

    t.forward(hauteur) #trace la branche
    t.right(angle/2) #rotation de depart pour la premiere tracer la premiere branche a droite

    for i in range(nb_branche):

      arbre(hauteur/2, profondeur-1, (epaisseur*2)/3, ( ((couleur[0]*2)/3), ((couleur[1]*6)/5), ((couleur[2]*8)/7) ), angle, nb_branche) #execute a nouveau arbre avec des parametres varies avec le positionnement actuel

      t.left(angle/(nb_branche-1)) #rotation pour l'affichage de la branche suivante

    t.right(angle/(nb_branche-1)) #annule la toute derniere rotation (boucle for au dessus) pour que l'ecart restant soit angle/2
    t.right(angle/2) #retour a l'angle initial


    t.penup() #retour en arriere, fonctions penup pour eviter de laisser une trace (qui n'est pas esthetique)
    t.backward(hauteur) #8*4 ; 32
    t.pendown()


#decallage de depart pour l'arbre
t.penup()
t.left(90)
t.backward(395)
t.pendown()

arbre(400, 3, 30, (200, 110, 25), 180, 4) #chene hypersymmetrique

t.penup()
t.left(-90)
t.forward(850)
t.left(90)
t.pendown()

arbre(300, 5, 50, (120, 120, 120), 240, 3) #gros sapin bleu des landes

t.penup()
t.left(-90)
t.backward(100)
t.left(90)
t.pendown()

arbre(600, 2, 10, (250, 250, 220), 70, 3) #giclette blanche

#giclette blanche, espece tres fertile et endemique de la foret vierge,
#elle se rigidifie rapidement en presence de predateurs.



for i in range (20): #generation de nombreux arbres avec des parametres aleatoires
  t.penup()
  t.goto(randint(-300, 300), randint(-300, 300)) #deplacement aleatoire sur la zone de dessin
  t.pendown()
  arbre(randint(10, 100), randint(2, 6), randint(10, 20), (randint(150, 255), randint(80, 200), randint(25, 100)), randint(79, 90), randint(2, 4)) #trace de l'arbre (avec bug inexplicable occasionnel qui fait pencher les arbres. Je pense que c'est lie a turtle, les premiers arbres avec les memes parametres bug de temps en temps mais pas tout le temps.)



