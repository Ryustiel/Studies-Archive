#INFO : les color code comme '\033[1;37m' dans les textes sont... bah des color code.
#en fait c'est tout ce que jvoulais dire, c'est pour ça que les textes des print sont illisibles lorsque lus directement dans le code.


#mache pas

#import tkinter
#from tkinter import Tk
#root = Tk()
#root.mainloop()

#autres Ressources
#https://tdhopper.com/blog/testing-whether-a-python-string-contains-an-integer/

#imports
import time
import datetime
import replit

#le reste
print("\033[1;30m ")
replit.clear()


#fonction qui sert à trouver une lettre saisie dans un mot saisi au préalable, ainsi que l'emplacement de chacune
def findTDT(objet, chr2Find, Interface=False):

  objet = str(objet)
  chr2Find = str(chr2Find)

  language = False
  chrCount = 0

  if(Interface == False):
    emplacement = "\033[1;31m"
    pluriel = "\033[1;37m au niveau du rang "
  else:
    emplacement = ""
    pluriel = " au niveau du rang "

  #analyse le mot
  for x1 in range(len(objet)):
    if(language == False):
      if(objet[x1] == chr2Find):
        chrCount = chrCount + 1
        emplacement = emplacement + str(x1 + 1)
        language = True
      
    else:
      if(objet[x1] == chr2Find):
        chrCount = chrCount + 1

        emplacement = emplacement + ", " + str(x1 + 1)

        if(Interface == False):
          if(pluriel != "\033[1;37m au niveau des rangs "):
            pluriel = "\033[1;37m au niveau des rangs "
        else:
          if(pluriel != " au niveau des rangs "):
            pluriel = " au niveau des rangs "

  #affichage
  if(Interface == False):
    if(chrCount == 0):
      if(len(chr2Find) == 1):
        return "\n\033[1;37my'a rien..."
      else:
        return "\n\033[1;31mJ'ai dit UNE SEULE lettre --'"

    else:
      return "\n\033[1;37mY'a \033[1;32m" + str(chrCount) + "\033[1;37m fois la lettre \033[1;34m" + str(chr2Find) + str(pluriel) + str(emplacement) + "\033[1;37m dans \033[1;33m" + str(objet)
  else:
    if(chrCount == 0):
      if(len(chr2Find) == 1):
        return "\ny'a rien..."
      else:
        return "\nJ'ai dit UNE SEULE lettre --'"

    else:
      return "\nY'a " + str(chrCount) + " fois la lettre " + str(chr2Find) + str(pluriel) + str(emplacement) + " dans " + str(objet)



#fonction d'étoilage. [Rajoute des étoiles entre les lettres]
def starry(objet, Interface=False):

  objet = str(objet)
  if(Interface == False):
    stock = "\n"
  else:
    stock = ""

#ajout d'étoiles à la bonne place dans une nouvelle string
  for x2 in range(len(objet)):
    if(x2 != len(objet) - 1):
      if(Interface == False):
        stock = stock + objet[x2] + "\033[1;33m*\033[1;32m"
      else:
        stock = stock + objet[x2] + "*"

    else:
      stock = stock + objet[x2]

#return du mot avec les étoiles
  return stock



#donne l'inverse du mot et l'indication True ou False si il est palyndrome
#la fonction ne donne pas de résultat T/F mais un texte lorsqu'elle est appelée avec Interface=True, car les dialog de RemI ne supportent pas les bool.
def invert(objet, Interface=False):

  objet = str(objet)
  invertedStr = str("")

#inversion
  for count in range(len(objet)):
    invertedStr = invertedStr + objet[-count-1]

  if(Interface == False):
    print("\033[1;37mInverse >\033[1;33m", invertedStr)

#détection palyndrome
  if(Interface == False):
    if(objet == invertedStr):
      print("\n\033[1;37mEt les deux trucs sont pareils")
      return True
    else:
      return False
    
  else:
    if(objet == invertedStr):
      print("\nEt les deux trucs sont pareils")
      return str("True ; Inverse > " + invertedStr) 
    else:
      return str("False ; Inverse > " + invertedStr)



#flood la console avec des maths pendant 20 ticks
def flood():
  nya = 0
  blah = 2
  while(nya < 16):
    blah = blah * blah
    print("\033[1;36mUNEXPECTED ERROR", blah)
    nya = nya + 1



#date
def date():
  date = str(datetime.datetime.now())
  return date




#menu . objectif du programme
quit = False
def ConsoleMenu(RemI2Exit=0):

  #menu first boot
  menu = True
  FIRSTmenu = True

  #menuTxT as a function pour pouvoir le réafficher facilement par la suite.
  def menuTxT(RemI2Exit_menuTxT, Mset=-1):
      if(Mset==-1):
        if(RemI2Exit_menuTxT == 0):
          menu = str((input("\033[1;37m\n----------------------------------------\n\033[1;31m0 - Active le menu RemI, issu d'un code html généré par le module, puis termine la suite d'instructions principale du code python, donc le programme à proprement parler \nLe menu RemI est susceptible de ne pas fonctionner; \nCa dépend des utilisateurs connectés à l'instance replit \n\033[1;32m1 - Lettre \n\033[1;33m2 - Etoiles \n\033[1;32m3 - Truc palyndrome \n\033[1;37m4 - Repl's LocalTime\n\033[1;36m5 - Flood\n\n\033[1;37mDu Coup => ")))
        else:
          menu = str((input("\033[1;37m\n----------------------------------------\n\033[1;31m0 - Exit menu\n\033[1;32m1 - Lettre \n\033[1;33m2 - Etoiles \n\033[1;32m3 - Truc palyndrome \n\033[1;37m4 - Repl's LocalTime\n\033[1;36m5 - Flood\n\n\033[1;37mDu Coup => ")))
      else:
        menu = Mset

      return menu


  #menu loop
  while(menu==menu):

  #wait to display
    if(FIRSTmenu == False):
      input("\033[1;37m\nAppuie sur 'entrée' pour Continuer...")
      replit.clear()
    else:
      FIRSTmenu = False

    
    #vas y tape cque tu veux ça n'arrêtera pas le programme (test is digit + message d'erreur customisé)
    menu = str(menuTxT(RemI2Exit))

    while(str.isdigit(menu) == False):

      replit.clear()
      print('\033[1;31m\nLa saisie ne correspond pas à un entier.\nVeuillez réessayer.')
      menu = menuTxT(RemI2Exit)

    replit.clear()
    #Mset représente la valeur précédemment entrée dans menu par la fonction menuTxT qui demande un input dans la console, ça évite de répéter l'input pck menuTxT va prendre l'argument Mset en tant qu'input. (ça fait beaucoup de fois le mot input nan ?)
    Mset = menu
    menu = int(menuTxT(RemI2Exit, Mset))


    #evaluation de la valeur menu

    if(menu == 0):
      FIRSTmenu = True
      replit.clear()
      print('\033[1;31mStopped.\n\nNya.\n')
      break

    elif(menu == 1):
      arg1Stockage = str(input("\n\033[1;32mMot à étudier => \033[1;33m"))
      print(findTDT(arg1Stockage, str(input("\n\033[1;32mLettre UNIQUE à trouver => \033[1;34m"))))

    elif(menu == 2):
      print(starry(str(input("\n\033[1;33mTruc à étoiler => \033[1;32m"))))

    elif(menu == 3):
      tempInv = str(input("\n\033[1;32mMot à étudier => \033[1;33m"))
      print("\n\033[1;37mPalyndrome >\033[1;33m", invert(tempInv))

    elif(menu == 4):
      #actualise puis affiche la variable date
      print("\n\033[1;37m", date())

    elif(menu == 5):
      flood()

    else:
      FIRSTmenu = True
      replit.clear()
      print("\033[1;31m\nLa valeur saisie ne correspond à aucune de celles proposées dans le menu.\nVeuillez réessayer.")


#interface
import remi.gui as gui
from remi import start, App

#Code à comprendre
class MyApp(App):
    def __init__(self, *args):
        super(MyApp, self).__init__(*args)


    def main(self):
        container = gui.VBox(width=250, height=300, style={'margin': '50px auto', 'display': 'flex', 'flex-direction': 'column'})

        gridbox = gui.GridBox(width='200', height='150', style={'margin': '50px auto'})

        gridbox.define_grid(['ab', 'cd', 'ef'])

        self.lbl = gui.Label("Menu RemI")
        self.bt = gui.Button('Rallumer le menu Console')
        self.bt2 = gui.Button("Flood", width = 80, height = 50, style={'margin': '5px'})
        self.bt3 = gui.Button("FindIT", width = 80, height = 50, style={'margin': '5px'})
        self.bt4 = gui.Button("Etoiles", width = 80, height = 50, style={'margin': '5px'})
        self.bt5 = gui.Button("Palyndrome", width = 80, height = 50, style={'margin': '5px'})
        self.bt6 = gui.Button("Time", width = 80, height = 50, style={'margin': '5px'})
        self.bt7 = gui.Button("Egg", width = 80, height = 50, style={'margin': '5px'})

        # setting the listener for the onclick event of the button ('s' now cuz i made many)
        self.bt.onclick.do(self.BTaction, 0)
        self.bt2.onclick.do(self.BTaction, 1)
        self.bt3.onclick.do(self.BTaction, 2)
        self.bt4.onclick.do(self.BTaction, 3)
        self.bt5.onclick.do(self.BTaction, 4)
        self.bt6.onclick.do(self.BTaction, 5)
        self.bt7.onclick.do(self.BTaction, 6)

        # appending a widget to another, the first argument is a string key
        container.append(self.lbl)
        container.append(self.bt)
        gridbox.append({'a' : self.bt2, 'b' : self.bt3, 'c' : self.bt4, 'd' : self.bt5, 'e' : self.bt6, 'f' : self.bt7})

        container.append(gridbox)

        # returning the root widget
        return container
      


    # fonction result du bouton on click
    def BTaction(self, widget, action):

      replit.clear()

      #vrai input de texte
      def vrai_dialog(self, Titre, Message, Callback):

        #variables globales pour la sous fonction dialogue_confirmed()
        global vrai_dialog_global_title
        vrai_dialog_global_title = Titre
        global vrai_dialog_global_callback
        vrai_dialog_global_callback = Callback

        def dialogue_confirmed(widget, sortie):
          global vrai_dialog_global_title
          global vrai_dialog_global_callback
          if(vrai_dialog_global_callback == chr2FindDialog):
            vrai_dialog_global_callback(sortie, Interface = True)
          else:
            fenetre = gui.GenericDialog(title = vrai_dialog_global_title, message = vrai_dialog_global_callback(sortie, Interface = True), width = '500px')
            fenetre.show(self)

        inDialog = gui.InputDialog(title=Titre, message=Message, width='500px')
        inDialog.show(self)
        inDialog.confirm_value.do(dialogue_confirmed)


      #fonction complémentaire à findTDT() : répète la boite de dialogue pour l'argument chr2find
      def chr2FindDialog(findTDT_objet, Interface):

        #variables globales pour la sous fonction dialogue_confirmed()
        global chr2FindDialog_global_findTDT_objet
        chr2FindDialog_global_findTDT_objet = findTDT_objet

        def dialogue_confirmed(widget, sortie):
          global chr2FindDialog_global_findTDT_objet
          fenetre = gui.GenericDialog(title = vrai_dialog_global_title, message = findTDT(chr2FindDialog_global_findTDT_objet, sortie, Interface=True), width = '500px')
          
          fenetre.show(self)

        inDialog = gui.InputDialog(title="FindIT", message="Entrez un unique caractère à rechercher dans la saisie précédente", width='500px')
        inDialog.show(self)
        inDialog.confirm_value.do(dialogue_confirmed)


      if(action == 0):
        ConsoleMenu(RemI2Exit=1)

      elif(action == 1):
        flood()

      elif(action == 2):
        vrai_dialog(self, "FindIT", "Entrez le texte à étudier", chr2FindDialog)

      elif(action == 3):
        vrai_dialog(self, "Etoiles", "Entrez le texte à étoiler", starry)

      elif(action == 4):
        vrai_dialog(self, "Palyndrome", "Entrez le texte à étudier", invert)

      elif(action == 5):
        dateDialog = gui.GenericDialog(title='Heure des serveurs de Repl.it', message=date(), width='250px')
        dateDialog.show(self)

      elif(action == 6):
        self.eggFunction()



    #EggFunction [this is not an intended feature of the program]
    def eggFunction(self):
      global egg_countdown
      egg_countdown = 0
   
      egg_container = gui.GenericDialog(width=300, height=500, style={'margin': '100px auto'})
      
      egg_button = gui.Button("Click Me in order to reach the egg", width = 100, height = 100, style={'margin': '65px'})
      egg_container.append(egg_button)

      egg_container.show(self)

      #contenu et position des boutons
      def egg_action(self):
        global egg_countdown
        egg_countdown = egg_countdown + 1

        egg_button2 = gui.Button("Im feeling meh ya know ?", width = 100, height = 100, style={'margin': '40px'})
        egg_label = gui.Label(" ", style={'margin':'40px'})

        def egg_label_edit_bt2(self):
          egg_label.set_text("https://justpaste.it/5k6na")
        egg_button2.onclick.do(egg_label_edit_bt2)

        if(egg_countdown == 1):
          egg_button.set_text("Clickez ici")
          egg_button.set_style({'margin': '20px'})
        elif(egg_countdown == 2):
          egg_button.set_text("This way")
          egg_button.set_style({'margin': '110px'})
        elif(egg_countdown == 3):
          egg_button.set_text("On se rapproche...")
          egg_button.set_style({'margin': '600px'})
        elif(egg_countdown == 4):
          egg_button.set_text("There is just 20 ish buttons left")
          egg_button.set_style({'margin': '40px'})
        elif(egg_countdown == 5):
          egg_button.set_text("Prépare toi à clicker")
          egg_button.set_style({'margin': '140px'})
        elif(6 <= egg_countdown <= 16):
          egg_button.set_text('plus que '+str(egg_countdown * -1 + 18)+' clicks...')
          egg_button.set_style({'margin': str((egg_countdown * -1 + 18)*30)+"px"})
        elif(egg_countdown == 17):
          egg_button.set_text("plus que 1 click...")
          egg_button.set_style({'margin': '150px'})
        elif(egg_countdown == 18):
          egg_button.set_text("lol jk")
          egg_button.set_style({'margin': '0px'})
        elif(egg_countdown == 19):
          egg_button.set_text("✨")
          egg_button.set_style({'margin': '125px'})
          egg_container.append(egg_label)
          egg_container.append(egg_button2)
        elif(20 <= egg_countdown <= 24):
          egg_button.set_text('allez !\nencore '+str(egg_countdown * -1 + 27)+' clicks :3')
          egg_button.set_style({'margin': str((egg_countdown * -1 + 27)*25)+"px"})
        elif(egg_countdown == 25):
          egg_button.set_text("allez !\nencore 2 clicks :3")
          egg_button.set_style({'margin': '1000px'})
        elif(egg_countdown == 26):
          egg_button.set_text("allez !\nencore 1 click :3")
        elif(egg_countdown == 27):
          egg_button.set_text("C'est l'avant avant dernier bouton")
          egg_button.set_style({'margin': '140px'})
        elif(egg_countdown == 28):
          egg_button.set_text("Two more and...")
          egg_button.set_style({'margin': '180px'})
        elif(egg_countdown == 29):
          egg_button.set_text("맞춰봐")
        elif(egg_countdown == 30):
          egg_button.set_text("you reached the egg ! Check the link below | OK and CANCEL allow leaving")
          egg_button.set_style({'margin': '0px'})
          egg_button2.set_style({'margin': '0px'})
          egg_label2 = gui.Label("https://youtu.be/-krt9AVHxxw?t=60", style={'margin':'40px'})
          egg_container.append(egg_label2)



      egg_button.onclick.do(egg_action)



ConsoleMenu()

# starts the web server
start(MyApp, debug=False, address='0.0.0.0', port=0, multiple_instance=True)
