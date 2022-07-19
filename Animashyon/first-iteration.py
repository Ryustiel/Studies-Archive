#imports...
from tkinter import *
import replit
import random

#attributs de la fenêtre TKinter
core = Tk()
core.title("Main Window")
core.geometry(str(core.winfo_screenwidth()) + "x" + str(core.winfo_screenheight()))

#attributs du canvas, association de l'app à "sheet"
sheet = Canvas(core, width=core.winfo_screenwidth(), height=core.winfo_screenheight(), background='light gray')
sheet.pack(padx=4, pady=4)

#creation des variables BallID et FloorID contenant les données des formes géométriques du canvas 
#(permettra par la suite de les désigner dans les commandes de TKinter)
#et BendboxData contenant les variables relatives à la déformation et au mouvement de l'objet auquel l'identifiant (premier indice spécifié) correspond. 
BallID = []
FloorID = []
BallData = []

#1 ==== Fonctions de Génération et d'Attribution des Identifiants ====

#intermédiaire pour "create_oval" : ajoute un espace dans les tableaux BallID et BallData qui correspondent au même identifiant dans leur tableaux respectifs, génère la forme et remplis avec les données adéquates.
def createBall(x=200, y=200, size=40, maxbend=20, vx=0, vy=0, leftwards = False, upwards = False, color='orange'):
  BallID.append(sheet.create_oval(x - size, y - size, x + size, y + size, fill=color))
  BallData.append([size, maxbend, vx, vy, upwards, leftwards, 0, 0, vy])
 
#intermédiaire pour "create_rectangle" : génère la forme et l'ajoute dans un nouvel espace du tableau (qui lui permettra d'être retenu comme plateforme)
def createFloor(x=200, y=400, width=60, color='orange'):
  FloorID.append(sheet.create_rectangle(x - width, y - 10, x + width, y + 20, fill=color))

#2 - ==== GESTION DE LA BENDBOX ====

#la bendbox c'est la zone dans laquelle un objet peut se déformer (réprésenté par le rayon de base de la balle (size) et le "maxbend", la réduction maximale de ce rayon au contact d'une surface)

#test pour un objet de référence d'identifiant 'IDa' si un de ses points de coordonnées correspond à ceux d'une des formes renseignées dans "FloorID" (= si ils se touchent)
#Renvoie True si c'est le cas, sinon False
def collide(IDa):
  for IDb in range(len(FloorID)):
    if ( 
      (sheet.coords(FloorID[IDb])[0] < sheet.coords(BallID[IDa])[0] < sheet.coords(FloorID[IDb])[2] 
      or sheet.coords(FloorID[IDb])[0] < sheet.coords(BallID[IDa])[2] < sheet.coords(FloorID[IDb])[2]) 
      and (sheet.coords(FloorID[IDb])[1] < sheet.coords(BallID[IDa])[1] < sheet.coords(FloorID[IDb])[3] 
      or sheet.coords(FloorID[IDb])[1] < sheet.coords(BallID[IDa])[3] < sheet.coords(FloorID[IDb])[3]) == True):
        return True
  return False

#3 - ==== MOUVEMENT ====

#vélocité / déformation
#bending; conversion => facteur de distortion <= taux de vélocité convertie en distortion
#gère le mouvement des balles en fonction de leur direction fournie en input, des paramètres de vélocité, de direction, de distortion, et des contraintes physiques.
def physics(ID, Xwards):

  #associe les données de la balle à des variables non-tab pour plus de lisibilité 
  size = BallData[ID][0]
  maxbend = BallData[ID][1]
  #valeurs de vélocité sur les axes x et y
  vx = BallData[ID][2]
  vy = BallData[ID][3]
  #deux variables boléeennes (gauche:True/False et haut:True/False) qui en se combinant indiquent le sens de la balle
  leftwards = BallData[ID][4]
  upwards = BallData[ID][5]
  #vitesse originale et maximale en descente d'une balle
  truespeed = BallData[ID][8]

  #mouvement sur l'axe Y
  if (Xwards == False):
    if (upwards == False):
      #déplacement récurrent de 1 unité dans la direction associée au couple Xwards/upwards
      #vers le bas
      sheet.move(BallID[ID], 0, 1)
      if (collide(ID) == True):
        #test si il est toujours possible de distordre la balle (par rapport à la valeur maxbend), la distord si oui, sinon, met "upwards" en True (BallData[ID][5])
        if (sheet.coords(BallID[ID])[3] - sheet.coords(BallID[ID])[1] > 2*size - maxbend):
          sheet.coords(BallID[ID], sheet.coords(BallID[ID])[0], sheet.coords(BallID[ID])[1], sheet.coords(BallID[ID])[2], sheet.coords(BallID[ID])[3]-1)
        else:
          BallData[ID][5] = True

      #(en upwards = False) augmente la vitesse de la balle jusqu'à sa vitesse maximale de chute (truespeed)
      #plus on se rapproche de 0 vy, plus la vitesse est importante (vy est la fréquence du déplacement d'un pixel sur l'axe y)
      if (vy > truespeed): 
        BallData[ID][3] = vy / 1.02
      else:
        BallData[ID][3] = truespeed

    else:
      #déplacement récurrent de 1 unité dans la direction associée au couple Xwards/upwards
      #vers le haut
      sheet.move(BallID[ID], 0, -1)
      #annule la distortion de la balle, la fait revenir à son état initial
      if (sheet.coords(BallID[ID])[3] - sheet.coords(BallID[ID])[1] < 2*size):

        sheet.coords(BallID[ID], sheet.coords(BallID[ID])[0], sheet.coords(BallID[ID])[1], sheet.coords(BallID[ID])[2], sheet.coords(BallID[ID])[3]+1)

      #réduit la vitesse de la balle jusqu'à un certain seuil (selon la vitesse de base (truespeed)) puis passe upwards (BallData[ID][5]) en False, ce qui correspond au moment où le rebond de la balle atteint son altitude maximale
      if (vy < truespeed*8):
        BallData[ID][3] = vy * 1.01
      else:
        BallData[ID][5] = False

    #lorsque sous une certaine ordonnée (hors de la zone de visibilité des plateformes), immobilise la balle. (pour réduire le lag)
    if (sheet.coords(BallID[ID])[3] == sheet.winfo_height()+140):
      BallData[ID][8] = 0
      BallData[ID][3] = 0
      BallData[ID][2] = 0
      flash(True)

  #mouvement sur l'axe X
  else:
    if (leftwards == False):
      #déplacement récurrent de 1 unité dans la direction associée au couple Xwards/upwards
      #vers la droite
      sheet.move(BallID[ID], 1, 0)
      #inverse le sens du mouvement de la balle sur l'axe X (en inversant leftwards (BallData[ID][4]))
      #lorsqu'elle atteint la bordure droite du canvas
      if (sheet.coords(BallID[ID])[2] > sheet.winfo_reqwidth()-10):
        BallData[ID][4] = True
    else:
      #déplacement récurrent de 1 unité dans la direction associée au couple Xwards/upwards
      #vers la gauche
      sheet.move(BallID[ID], -1, 0)
      #inverse le sens du mouvement de la balle sur l'axe X (en inversant leftwards (BallData[ID][4])) 
      #lorsqu'elle atteint la bordure gauche du canvas
      if (sheet.coords(BallID[ID])[0] < 1):
        BallData[ID][4] = False

#déclenche la fonction "physics" pour chaque balle avec un délai qui dépend de vx (BallData[ID][2]) et vy (BallData[ID][3]) et du compteur associé (BallData[ID][6] et BallData[ID][7])
#sauf si la vélocité de l'axe est nulle, le compteur associé (à x ou à y) est incrémenté de 1 à chaque actualisation de la fonction.
#les vélocités correspondent à la valeur maximale que doit atteindre ce compteur pour lancer physic.
#chaque balle dispose de deux compteurs pour chaque axe (x et y).
def movement():
  for ID in range(len(BallID)):
    if (BallData[ID][2] != 0):
      if (BallData[ID][6] >= BallData[ID][2]):
        BallData[ID][6] = 0
        physics(ID, True)
      else:
        BallData[ID][6] = BallData[ID][6] + 1

    if (BallData[ID][3] != 0):
      if (BallData[ID][7] >= BallData[ID][3]):
        BallData[ID][7] = 0
        physics(ID, False)
      else:
        BallData[ID][7] = BallData[ID][7] + 1

  core.after(1, movement)

#4 - ==== GENERATION DES BALLES ====
#tableau contenant différents noms de couleurs pour être utilisés en tant que paramètre dans randomBall
colorTab = ["red", "green", "yellow", "orange", "cyan", "lime", "purple", "magenta", "pink"]

#exécute createBall avec des valeurs aléatoires (dans un certain interval pour éviter des proportions trop extrêmes)
#cette fonction sera exécutée à chaque clic sur le bouton intégré au canvas pour générer une nouvelle balle.
def randomBall(void=True):
  randomSize = random.randint (20, 60)
  
  createBall(x=random.randint (0, sheet.winfo_reqwidth()), y=random.randint (0, sheet.winfo_reqheight()-300), 
  size=randomSize, maxbend=(randomSize / random.randint(2, 4)), 
  color=colorTab[random.randint (0, len(colorTab)-1)], 
  vy=random.randint(1, 3), vx=random.randint(1, 10), 
  upwards=bool(random.getrandbits(1)), leftwards=bool(random.getrandbits(1)))

#5 - ==== ANIMATIONS ====
#lorsque la fonction est appelée avec (spawn = True), fait apparaître un rectangle blanc (désigné par "flashObject") en bas du canvas, sinon, supprime un rectangle existant.
def flash(spawn=False):
  global flashObject

  if spawn == True:
    flashObject = sheet.create_rectangle(0, sheet.winfo_reqheight(), sheet.winfo_reqwidth(), sheet.winfo_reqheight()-20, fill='white')
    core.after(500, flash)
  else:
    sheet.delete(flashObject)


#==== Boot ====
#exécute create floor sans action de l'utilisateur pour avoir quelques plateformes démo à l'éxécution du programme
createFloor(width=600, y=450)
createFloor(width=100, x=200, y=400)
createFloor(width=50, x=500, y=250)

#bouton : structure (fonctions liée à l'affichage du bouton et de son texte)
boutonP1 = sheet.create_rectangle(20, 20, 120, 50, width=0, fill="purple", activefill='pink')
boutonP2 = sheet.create_text(70, 36, text="Random Ball")
#bouton : click event (lie le clic sur le bouton à l'exécution de la fonction randomBall)
sheet.tag_bind(boutonP1, "<Button-1>", randomBall)
sheet.tag_bind(boutonP2, "<Button-1>", randomBall)

#affichage des instructions console
replit.clear()
print("Nouvelle Balle : 'createBall(x (int), y (int), size (int), maxbend (int), vx (int), vy (int), leftwards (bool), upwards (bool), color (str (color name ou couleur hexadécimale)))'\n\n(valeurs par défaut : x=200, y=200, size=40, maxbend=20, vx=0, vy=0, leftwards = False, upwards = False, color='orange')\n\n\n\nNouvelle Plateforme : 'createFloor(x (int), y (int), width (int), color (str (color name ou couleur hexadécimale)))'\n\n(valeurs par défaut : x=200, y=400, width=60, color='orange')\n\n\n\n")

#boucle 'movement', mise à jour de la physique
movement()
#éxécution de TKinter
core.mainloop()
