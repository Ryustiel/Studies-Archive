import random
global selectedCourse
selectedCourse = "None"
#config[0] = WeightMode
global config
config = [True]
#liste [[str|nom d'élève, int|0-9 poids]]
global liste
liste = []

def config():
  loaded = open("aaconfig.txt", "r")
  if (loaded[11] == "0"):
    config[0] = False
    print("WeightMode:Disabled")
  else:
    config[0] = True
    print("WeightMode:Enabled")

#file manipulation
def load(course):
  global liste
  global selectedCourse
  #safety save
  if (selectedCourse != "None"):
    save(selectedCourse)

  selectedCourse = course


  #managing files
  loaded = open(course+".txt", "r+")
  cache = loaded.read()

  #gathering
  record = False
  liste = []
  name = ""

  for charID in range(len(cache)):

    #name registration mode on
    if (record == True):
      
      #new name => means no weight specified
      if (cache[charID] == "#"):
        liste.append([name, 8])
        name = ""
      #weight specified, gathering value
      elif (cache[charID] == ";"):
        liste.append([name, int(cache[charID+2]+cache[charID+3])])
        name = ""
        record = False
      #basic name character gathering loop
      elif (charID != 0):
        if (cache[charID] != "\n"):
          name = name + cache[charID]

    #name registration mode
    else:
      if (cache[charID] == "#"):
        record = True
  #last item weight unspecified
  if (len(name) != 0):
    liste.append([name, 8])
  
  #unload
  print('\nloaded "'+course+'"_____\n')
  loaded.close()
def save(course):
  loaded = open(course+".txt", "w+")

  for itemID in range(len(liste)):
    if (liste[itemID][1] < 10):
      loaded.write("#"+ liste[itemID][0] +"; 0"+ str(liste[itemID][1]) +"\n")
    else:
      loaded.write("#"+ liste[itemID][0] +"; "+ str(liste[itemID][1]) +"\n")

  loaded.close()

#random picker
def pick(PickerRange=1):
  global liste
  global config
  weighted_eleves = []
  targetlist = []

  print("--------------------------------")

  for i in range(PickerRange):
    #generate (unefficiently) a list of multiple names based on weight property
    for eleveid in range(len(liste)):
      for weight in range(liste[eleveid][1]):
        weighted_eleves.append(liste[eleveid][0])
    #preventing "no eleve error"
    if (weighted_eleves == []):
      weighted_eleves.append("None")

    #random choice from the weighted list
    target = random.choice(weighted_eleves)
    #reset random tab
    weighted_eleves = []
    #reset weight
    for eleveid in range(len(liste)):
      if (liste[eleveid][0] == target):
        liste[eleveid][1] = -1
    #final list (can feature multiple names)
    targetlist.append(target)

  #updating weight
  for eleveid in range(len(liste)):
      if (liste[eleveid][1] < 99):
        liste[eleveid][1] = liste[eleveid][1]+1

  #display...
  output = "\n"+str(PickerRange)
  if (PickerRange == 1):
    output = output +" élève => "+ targetlist[0] +"\n"
  else:
    output = output + " élèves...\n\n"
    for name in range(len(targetlist)):
      output = output + str(name+1) +"| "+ targetlist[name] +"\n"

  save(selectedCourse)
  print(output+"\n--------------------------------\n")

#data
#average
def meanValue():
  global liste
  average = 0

  for item in range(len(liste)):
    average = average + liste[item][1]

  return (average / len(liste))
#median
def middleValue():
  global liste
  median = []

  #collect values to sort
  for item in range(len(liste)):
    median.append(liste[item][1])

  #sort then pick up the middle value (half of "sorted"s length)
  return (sorted(median)[int(len(liste)/2)])
  
#display
def data(action=0):
  print("--------------------------------\n")

  if (action == 0):
    print("poids moyen de la classe : "+str(meanValue())+"\npoids médian : "+ str(middleValue())+"\n")

  #below median
  elif (action == "-median"):
    comparatif = middleValue()
    for itemID in range(len(liste)):
      if (liste[itemID][1] < comparatif):
        print("#"+ liste[itemID][0] +"; "+ str(liste[itemID][1]) +"\n")
  #below average
  elif (action == "-average"):
    comparatif = meanValue()
    for itemID in range(len(liste)):
      if (liste[itemID][1] < comparatif):
        print("#"+ liste[itemID][0] +"; "+ str(liste[itemID][1]) +"\n")
  #above median
  elif (action == "+median"):
    comparatif = middleValue()
    for itemID in range(len(liste)):
      if (liste[itemID][1] > comparatif):
        print("#"+ liste[itemID][0] +"; "+ str(liste[itemID][1]) +"\n")
  #above average
  elif (action == "+average"):
    comparatif = meanValue()
    for itemID in range(len(liste)):
      if (liste[itemID][1] > comparatif):
        print("#"+ liste[itemID][0] +"; "+ str(liste[itemID][1]) +"\n")

  print("--------------------------------\n")


#help
def help():
  print("this is help")

#mode easy input; mode 1/0, sélection équitable ABSOLUE; Sélection sans reset de poids, et SELON LA MEDIANNE (- souvent choisis) et SELON VALEUR CHOISIE

load("bwah")