class Graphe:
    """un graphe représenté par une matrice d'adjacence,
       où les sommets sont les entiers 0,1,...,n-1"""

    def __init__(self, n):
        self.n = n
        self.adj = [[False] * n for _ in range(n)] #matrice de dimention n (ct a dire objet [False] sur n items d'une liste, instruction repetee (for _ in range(n)))

    def ajouter_arc(self, s1, s2, double=False):
        self.adj[s1][s2] = True #ecrit arc pour arbre oriente (sinon "self.adj[s2][s1]")
        if double: #cree un arc en sens inverse
          self.adj[s2][s1] = True

    def arc(self, s1, s2):
        return self.adj[s1][s2]

    def voisins(self, s):
        v = []
        for i in range(self.n): #recherche les valeurs pour i abscisses
            if self.adj[s][i]:
                v.append(i)
        return v

    def afficher(self):
      for i in range(self.n):
        print(i, "=>", self.voisins(i))
        print(f"{i} => {self.voisins(i)}") #le format

    def nb_sommets(self):
      return self.n

    def sommets(self):
      """renvoie un tuple des valeurs du graphe"""
      return range(self.n)

    def degre(self, s):
      sommets = 0
      for i in range(self.n): #lecture abscisses
        if self.adj[s][i]:
          sommets = sommets + 1
      return sommets

    def nb_arcs(self):
      sommets = 0
      for i in range(self.n):
        for j in range(self.n):
          if self.adj[i][j]:
            sommets = sommets + 1
      return sommets

    def supprimer_arc(self, s1, s2):
      self.adj[s1][s2] = False

def mex(voisins, couleur):
    """la plus petite couleur non utilisée par les voisins"""
    n = len(voisins) #nombre de voisins (couleurs uniques nécessaires)
    dispo = [True] * (n + 1) #tableau de disponibilite des couleurs
    for v in voisins:
        if v in couleur and couleur[v] <= n: #[sécurité] si voisin a d&jà une couleur (référencée dans dico) ETµ?!?
            dispo[couleur[v]] = False #couleur rendue indisponible si elle ne l'est pas déjà (indice du tableau retournant un False)
    for c in range(n + 1): #normalement le couleur[v] <= n permet d'ajouter la couleur (n+1) : je crois
        if dispo[c]: #ajoute premiere couleur disponible
            return c
    assert False # on n'arrivera jamais ici

def coloriage(g):
    """colorie graphe g avec un algorithme glouton"""
    couleur = {} #les couleurs seront des integer
    n = 0
    for s in g.sommets(): #MODIFIE POUR NB_SOMMETS() : CORRESPONDANCE A GRAPHE
        c = mex(g.voisins(s), couleur) #mex retourne un identifiant de couleur (1, 2, 3, 4...)
        couleur[s] = c #stock la couleur associee à s
        n = max(n, c + 1) #si la derniere couleur ajoutee est grosse, n la vaut, n = max de couleurs donc
        if (n > 4): #DEBUT DE LIGNE AJOUTEE
          print("Le théorème des 4 couleurs n'est pas respecté") #FIN DE LIGNE AJOUTEE
    return couleur, n #donnees de couleurs, et de nombre de couleurs

g = Graphe(18) #genere le graphe
id={"Hauts-de-France":0, "Normandie":1, "Ile-de-France":2, "Grand Est":3, "Bretagne":4, "Pays de la Loire":5, "Centre-Val de Loire":6, "Bourgogne-France-Compté":7, "Nouvelle-Aquitaine":8, "Auvergne-Rhöne-Alpes":9, "Occitanie":10, "Provence-Alpes-Côte d'Azur":11, "Guadeloupe":12, "Martinique":13, "Guyane":14, "Mayotte":15, "La Réunion":16, "Corse":17} #associe chaque region à une valeur (rang dans la matrice) pour faciliter la relecture des méthodes "ajouter_arc"

#génère la matrice d'adjacence qui représente les régions voisines d'une région donnée
#le paramètre "True" de ajouter_arc() fait générer également un arc entre la seconde région et la première (un lien dans les deux sens, un graph non orienté)
g.ajouter_arc(id["Hauts-de-France"], id["Normandie"], True)
g.ajouter_arc(id["Hauts-de-France"], id["Ile-de-France"], True)
g.ajouter_arc(id["Hauts-de-France"], id["Grand Est"], True)

g.ajouter_arc(id["Normandie"], id["Bretagne"], True)
g.ajouter_arc(id["Normandie"], id["Pays de la Loire"], True)
g.ajouter_arc(id["Normandie"], id["Centre-Val de Loire"], True)
g.ajouter_arc(id["Normandie"], id["Ile-de-France"], True)

g.ajouter_arc(id["Ile-de-France"], id["Centre-Val de Loire"], True)
g.ajouter_arc(id["Ile-de-France"], id["Bourgogne-France-Compté"], True)
g.ajouter_arc(id["Ile-de-France"], id["Grand Est"], True)

g.ajouter_arc(id["Grand Est"], id["Bourgogne-France-Compté"], True)

g.ajouter_arc(id["Bretagne"], id["Pays de la Loire"], True)

g.ajouter_arc(id["Pays de la Loire"], id["Nouvelle-Aquitaine"], True)
g.ajouter_arc(id["Pays de la Loire"], id["Centre-Val de Loire"], True)

g.ajouter_arc(id["Centre-Val de Loire"], id["Nouvelle-Aquitaine"], True)
g.ajouter_arc(id["Centre-Val de Loire"], id["Bourgogne-France-Compté"], True)
g.ajouter_arc(id["Centre-Val de Loire"], id["Auvergne-Rhöne-Alpes"], True)

g.ajouter_arc(id["Bourgogne-France-Compté"], id["Auvergne-Rhöne-Alpes"], True)

g.ajouter_arc(id["Nouvelle-Aquitaine"], id["Occitanie"], True)
g.ajouter_arc(id["Nouvelle-Aquitaine"], id["Auvergne-Rhöne-Alpes"], True)

g.ajouter_arc(id["Auvergne-Rhöne-Alpes"], id["Occitanie"], True)
g.ajouter_arc(id["Auvergne-Rhöne-Alpes"], id["Provence-Alpes-Côte d'Azur"], True)

g.ajouter_arc(id["Occitanie"], id["Provence-Alpes-Côte d'Azur"], True)


#génère un coloriage du graphe g (fonction fournie)
carte = coloriage(g)

print("xux") #tests de debug
print(carte)
print (id.items(), "\n") 

colorid = ["orange", "violet", "vert  ", "cyan  "] #associe des noms aux identifiants de couleur (visuel, éditable par d'autres strings qui représentent des couleurs sans conséquence)

#attribue des noms aux valeurs à partir de dictionnaires et de tableaux d'association, afin de rendre le résultat plus lisible
for (region_identifier, color_identifier) in carte[0].items():
  for (region_name, region_identifier2) in id.items():
    if region_identifier == region_identifier2 :
      print(colorid[color_identifier], region_name)


#1 Implementer un graphe correspondant

#2. utiliser le programme de coloriage de graphe (pgrm38) (en expliquant son rôle et en mettant des commentaires sur le code)

#le programme coloriage associe une valeur à chaque sommet d'un graphe fournit en entrée.
#cette association est renvoyée dans un dictionnaire de la forme {id_graphe:valeur}
#la fonction mex détermine le valeur à utiliser en fonction des voisins et couleur construit le dictionnaire associant id et valeur et met à jour la valeur n

#3. imprimer le résultat. Quel est le théorème de coloriage de graphe ? (à trouver sur le net)

#il s'agit du théorème des 4 couleurs qui énonce qu'il est toujours possible de colorier une carte de pays avec quatres couleurs, carte dont les relations entre les espaces (joint ou distant) peuvent être représentés par un graphe.
#le théorème implique donc que pour tout graphe représentant des adjacences, il est possible avec quatres valeurs uniquement d'en affecter une à chaque sommet sans jamais associer la même valeur à deux sommets partageant la même arrête.

#4. Ce théorème est-il appliqué ici ? Comment modifier votre programme pour qu'il le soit ?

#le théorème se vérifie en observant le résultat, car le programme cherche à minimiser le nombre de couleurs utilisées (en essayant d'abord les plus petites valeurs), cependant, il est possible de renforcer cette vérification en ajoutant un message signalant le non respect eventuel de ce théorème. 

#on pourrait aussi simplement lire nous même la valeur n renvoyée par la fonction coloriage et regarder si elle est supérieure à 4, mais c'est automatisé par le "if" et le message d'erreur.



#Librairies pour création de widgets(curseur, bouton, .....) et manipulations d'images

# classe bouton
# http://tkinter.fdex.eu/doc/bw.html

depart={"Hauts-de-France":(100,30), "Normandie":(65,45), "Ile-de-France":(95,55), "Grand Est":(130,50), "Bretagne":(30,55), "Pays de la Loire":(60,70), "Centre-Val de Loire":(90,70), "Bourgogne-France-Compté":(120,80), "Nouvelle-Aquitaine":(70,110), "Auvergne-Rhöne-Alpes":(125, 110), "Occitanie":(90, 140), "Provence-Alpes-Côte d'Azur":(140, 140), "Guadeloupe":False, "Martinique":False, "Guyane":False, "Mayotte":False, "La Réunion":False, "Corse":(175, 165)}

tupcolors = [(255, 160, 0), (215, 0, 230), (120, 225, 0), (0, 235, 255)]

from tkinter import *
from os import system  # la bibliotheque PIL doit avoir ete installee
#system ('pip install Pillow')
from PIL import Image
def colorier() :
    global py
    py =Image.new("RGB",(200,200)) # conteneur de l'image transformée
    modif_carte()

    id = 0
    for (nom, coords) in depart.items():

      if coords != False:
        #print(tupcolors[carte[0][id]], coords, id)
        colorier_zone(coords[0], coords[1], tupcolors[carte[0][id]])
        #mettre_un_point(coords, (0, 0, 255))
      id += 1

    colorier_zone(90,70, (255, 0, 0))
    affichage(py)

decals = [] #generation d'un tableau de coefficients pour generer un carre de points a l'aide de la boucle for de la fonction mettre_un_point
for i in range(-3, 3):
  for j in range(-3, 3):
    decals.append((i, j))

def mettre_un_point(lcoords, couleur):
  """coords est un tuple (x, y), couleur est un tuple RGB
  place un carre de dimension (def de decals) de couleur a l'emplacement"""
  for i in range(len(decals)):
    py.putpixel((lcoords[0]+decals[i][0], lcoords[1]+decals[i][1]), couleur)

# fonction passant en noir et blanc avec un seuil
def modif_carte():

  global im

  for i in range(largeur):
      for j in range(hauteur):
          pixels=im.getpixel((i,j))
          moy = int((pixels[0]+pixels[1]+pixels[2])/3)
          # remplacer le pixel par blanc ou noir suivant que le niveau est clair ou non
          if(moy>250):
              py.putpixel((i,j),(255,255,255))
          else:
              py.putpixel((i,j),(0,0,0))

def colorier_zone(x, y, color, i=900): #i limite le nombre d'executions au cas où (limite de profondeur de recursion de replit)
  """
  genere un coloriage de la zone (partiel au dela d'une certaine surface ou de contours trop complexes)
  """
  if py.getpixel((x, y)) == (255, 255, 255) and x<200 and y<200 and x>0 and y>0 and i>0:
    py.putpixel((x, y), color)

    colorier_zone(x+1,y, color, i-1)
  
    colorier_zone(x-1,y, color, i-1)

    colorier_zone(x,y+1, color, i-1)

    colorier_zone(x,y-1, color, i-1)



# fonction affichant l'image originale et l'image transformée
def affichage(imag):
    imag.save('nb.png') # sauvegarde l'image transformée dans le fichier nb.png
     # affichage de l'image transformée
    imagtransf=PhotoImage(file='nb.png')
    can.create_image(5*200/2,200/2,image=imagtransf)
     # surveillance de la fenêtre
    Mafenetre.mainloop()

# création et édition des paramètres de la fenêtre contenant le canvas
Mafenetre = Tk()
Mafenetre.geometry('700x400')
can=Canvas(Mafenetre,width=1024,height=1024)
can.pack(padx=44,pady=44)
imj = Image.open('nb2.png')   # ouverture du fichier MonaLisa.png
im=imj.resize((200,200))   # redimensionnement de l'image 200*200
largeur , hauteur = im.size #stockage des dimensions dans 2 
bouton=Button(Mafenetre,text="Noir et Blanc",command=colorier,activebackground='#FF4149')
bouton.place(x="300",y="260")


# affichage images
# affichage de l'image originale : MonaLisa.png
imaorig=PhotoImage(file='nb2.png')
can.create_image(200/2,200/2,image=imaorig)


affichage(im)
