//mise à jour du texte de la page (autre page) en fonction de l'image qui déclenche la fonction (identifiée par picID)
//+gestion du score quand picID = 0
function image2title(picID){
  if(picID==0){
    text="Mango";
    if(score==0){
      successText="success";
      score=1;
    }
    else{
      score=score+1;
      successText="success("+score+")";
    }
    document.getElementById("success").innerHTML=successText;
    failure=false;
  }

  if(picID==1){
    text="Portal";
  }
  if(picID==2){
    text="Handmade Portal";
  }

  document.getElementById("picTitle").innerHTML=text;

  if(failure){
    setTimeout('alert("Nope")', 50);
  }
  else{
    failure=true;
  }
}

//applique le contenu de textbox au h1 de la page index
//déclenché par clic sur h1
function updateWelcome(){
  value = document.getElementById("textbox").value;
  if(value != ""){
    document.getElementById("welcome").innerHTML=value;
  }
}

//prend l'identifiant d'une barre (sans les.-a...) avec id et applique l'entier "progression" converti en pourcentage de remplissage aux deux barres a et b de manière à ce que la largeur des deux barres remplisse (presque) la largeur de l'écran.
function fillingBar(id, progression){
  if (progression < 100){
    document.getElementById(id+"-a").style.width = progression-1+"%";
    document.getElementById(id+"-b").style.width = 100-progression+"%";
    if (progression < 1){
      document.getElementById(id+"-a").style.width = "0%";
      document.getElementById(id+"-b").style.width = "99%";
    }
  }
  else{
    document.getElementById(id+"-a").style.width = "99%";
    document.getElementById(id+"-b").style.width = "0%";
  }
}

var progress = 0;
var fillBackwards = false;
//ajuste le remplissage de la barre jusqu'à la valeur de upto(%) en délayant son remplissage (1% / 20ms)
function timer(upto=0, firstexe=true){
  if (firstexe==true){
    if (progress <= upto){
      fillBackwards = false;
    }
    if (progress > upto){
      fillBackwards = true;
    }
  }
  if (fillBackwards == false){
    if (progress <= upto){
      progress = progress + 1;
      fillingBar('bar', progress);
      setTimeout('timer('+upto+', false)', 20);
    }
  }
  else{
    if (progress >= upto){
      progress = progress - 1;
      fillingBar('bar', progress);
      setTimeout('timer('+upto+', false)', 20);
    }
  }
}

//tableau contenant des éléments esthétiques de l'affichage des résultats.
randomTab = ["canapé", "chat", "UwU", "explosion", "iphones are trash", "coral reef", "blah", "paillettes", "portal", "sparkles"]

//format => [ID, question, right_answer, rep1, rep2, rep3, 0 || rep1L2*, rep2L2*, rep3L3]; contient les données des questions*
var questionTab = [[0]];

var questionID = 1;
var right_answer = 0;
var score = 0;
var questionCount = 10;
var randomGen = true;

//actualise les questions et modifie la question actuelle en fonction de nav 
//0 => question suivante; 1 => précédente; 2 => première question et réinitialisation de tous les éléments altérés par la progression du questionnaire.
function questionManager(nav){
//navigation (gestion de questionID =la question qui s'affiche)
  if (nav==2){
    //réinitialisations simples
    questionID = 1;
    score = 0;
    document.getElementById("scoreboard").innerHTML = "Score : "+score;

    //gestion de l'input question max
    if (isNaN(document.getElementById("question_count_input").value) == false 
    && document.getElementById("question_count_input").value != ""){
      questionCount = document.getElementById("question_count_input").value;
    }
    document.getElementById("question_count_input").value = questionCount;

    //disparition du dialog 'résultats'
    document.getElementById("endOfAll").innerHTML = "";
    document.getElementById("endOfAll").style["border-style"] = "none";

    timer(0);
    questionUpdater();
  }
  if (nav==0){
    questionID = questionID + 1;
    questionUpdater();
  }
  if (nav==1){
    questionID = questionID - 1;
    questionUpdater();
  }
}
//assignation des images et des questions en fonction de l'identifiant...
//; update
var counter
var entry
var quickdisplay = false
function questionUpdater(){

  //test question identifiée ou non, extraction et affichage des valeurs associées à l'identifiant depuis le questionTab, sinon génération de question aléatoire à partir de Math.random
  randomGen = true
  if (questionID <= questionCount){
    for (entry=0; entry < questionTab.length; entry++){
      if (questionTab[entry][0] == questionID){
        //éléments simples (intitulé et ID de la bonne réponse)
        document.getElementById("picTitle").innerHTML = questionTab[entry][1];
        right_answer = questionTab[entry][2];

        //affichage 'dynamique ~ ~ ' des réponses (questionTab[6] = 0); 1 seule ligne
        if (questionTab[entry][6] == "0"){
          for (counter=1; counter < 4; counter++){
            document.getElementById("L1ans"+counter).innerHTML = questionTab[entry][counter+2];
            document.getElementById("L0ans"+counter).innerHTML = "";
            document.getElementById("L2ans"+counter).innerHTML = "";
          }
        }
        else{
          for (counter=1; counter < 4; counter++){
            document.getElementById("L1ans"+counter).innerHTML = "";
            document.getElementById("L0ans"+counter).innerHTML = questionTab[entry][counter+2];
            document.getElementById("L2ans"+counter).innerHTML = questionTab[entry][counter+5];
          }
        }

        //mise à jour de l'affichage du num. de la question*
        document.getElementById("quick_display_input").value = questionID;
        randomGen = false
        break;
      }
    }
    if (randomGen == true){
      //géération de la valeur de la question
      var randomized_ans = Math.ceil(Math.random()*10/4);
      //éléments simples (intitulé et ID de la bonne réponse)
      document.getElementById("picTitle").innerHTML = "clickez sur "+randomized_ans;
      right_answer = randomized_ans;

      //affichage des réponses par défaut
      for (entry=1; entry < 4; entry++){
        document.getElementById("L1ans"+entry).innerHTML = entry;
        document.getElementById("L0ans"+entry).innerHTML = "";
        document.getElementById("L2ans"+entry).innerHTML = "";
      }
      
      //mise à jour de l'affichage du num. de la question*
      document.getElementById("quick_display_input").value = questionID;
    }
  }
    //Message de réussite
  else{
    document.getElementById("picTitle").innerHTML = "Résultats";
    document.getElementById("endOfAll").innerHTML = score+" réussites, "+(questionCount - score)+" ratés; sur "+questionCount+" questions, "+Math.round((score/questionCount)*100)+"% de réussite, en gros 1 sur "+Math.round(questionCount/score)+". "+randomTab[Math.floor((Math.random()-0.01)*10)]+".";
    document.getElementById("endOfAll").style["border-style"] = "solid";
  }
  //visuel de l'intitulé de la question
  if(quickdisplay == true){
    document.getElementById("picTitle").style["color"] = "rgba(205, 145, 105, 0.6)"
  }
  else{
    document.getElementById("picTitle").style["color"] = "rgba(105, 105, 105, 0.794)"
  }
  document.getElementById("picTitle").style.transform = "scale(1.3)";
}

//déclenchée par un clic sur une réponse; "answer" = numéro de la réponse [1,3]
//met à jour le score et gère son affichage au dessus de la fillingbar.
function checkOut(answer){
  if (quickdisplay == true){
    if (answer == right_answer){
      quickdisplay = false;
      questionManager(2);
    }
  }
  else{
    if (questionID <= questionCount){
      if (answer == right_answer){
        score = score + 1;
      }
      document.getElementById("scoreboard").innerHTML = "Score : "+score+" ; Failures : "+(questionID - score);
      timer(Math.round(questionID / questionCount * 100));

      questionManager(0);
    }
  }
}

//quickdisplay ; affiche la question correspondant à l'identifiant spécifié (sans compter le score, cliquer sur la bonne réponse pour revenir au début du quizz)
//modifie la couleur du titre pour indiquer l'état quickDisplay
function quickDisplayFunction(){
  if (isNaN(document.getElementById("quick_display_input").value) == false 
  && document.getElementById("quick_display_input").value != ""){
    questionID = (document.getElementById("quick_display_input").value)-1;
  }
  quickdisplay = true;
  questionManager(0);
  timer(Math.round(questionID / questionCount * 100));
}

//okcontent [id, question, alignement_coherence, right_answer]
var okcontent = [0, false, false, false]
var error
var chosen_answer = 0

//vérifie si le contenu des zones de texte est correct pour la génération des questions.
//génère et met à jour les messages d'erreur, gère le visuel du bouton "Ajouter"
function inputUpdate(){
  error = ""
  //test identifiant
  if (document.getElementById("qinput_id").value == "ID"
  || document.getElementById("qinput_id").value == ""){
    document.getElementById("qinput_id").style["border-color"] = "red";
    error = "Entrez un Identifiant";
    okcontent[0] = 0;
  }
  else{
    okcontent[0] = 1
    for (entry=0; entry < questionTab.length; entry++){
      if (document.getElementById("qinput_id").value==questionTab[entry][0]
      || isNaN(document.getElementById("qinput_id").value) == true){
        document.getElementById("qinput_id").style["border-color"] = "red";
        error = "Identifiant Invalide";
        okcontent[0] = 2;
        break
      }
    }
    if (okcontent[0] == 1){
      document.getElementById("qinput_id").style["border-color"] = "lime";
    }
  }

  //test bonne réponses
  if (chosen_answer == 0){
    error = "sélectionnez une bonne réponse en cliquant sur la case sous la zone de texte correspondante";
    okcontent[3] = false;
  }

  //test réponses
  okcontent[2] = true
  for (entry=1; entry < 4; entry++){
    if (document.getElementById("qinput_answerA"+entry).value == "Réponse "+entry
    || document.getElementById("qinput_answerA"+entry).value == ""){
      if (document.getElementById("qinput_answerB"+entry).value != "(Ligne 2*)"
      && document.getElementById("qinput_answerB"+entry).value != ""){
        document.getElementById("qinput_answerA"+entry).style["border-color"] = "red";
        error = "Replissez d'abord la première ligne";
        okcontent[2] = false;
      }
      else{
        document.getElementById("qinput_answerA"+entry).style["border-color"] = "red";
        error = "Entrez vos réponses";
      }
    }
    else{
      document.getElementById("qinput_answerA"+entry).style["border-color"] = "rgba(0, 0, 0, 0)";
    }
  }

  //test question
  if (document.getElementById("qinput_question").value == ""
  || document.getElementById("qinput_question").value == "Entrez votre Question"
  || document.getElementById("qinput_question").value == "Question Ajoutée"){
    document.getElementById("qinput_question").style["border-color"] = "red";
    error = "Entrez une Question";
    okcontent[1] = false;
  }
  else{
    document.getElementById("qinput_question").style["border-color"] = "rgba(0, 0, 0, 0)";
    okcontent[1] = true;
  }

  //bouton d'ajout
  document.getElementById("important_button").style.backgroundColor = "rgba(255, 255, 255, 0.2)";
  document.getElementById("important_button").style.color = "rgba(0, 0, 0, 0.4)";
  if (okcontent[0] == 1){
    counter = 0;
    for (entry=1; entry < 4; entry++){
      if (okcontent[entry] == true){
        counter = counter + 1;
      }
      else{
        break;
      }
    }
    if (counter == 3){
      document.getElementById("important_button").style.backgroundColor = "rgba(255, 255, 255, 1)";
      document.getElementById("important_button").style.color = "rgba(0, 0, 0, 1)";
    }
  }

  document.getElementById("error_message").innerHTML = error
}

//déclenchée par clic sur les cases à cocher; answerID = case[1, 3]
//gère le système de sélection et le visuel des cases; gère okcontent[3] qui est une condition pour la validation d'une question.
function chosenAnswerManager(answerID){
  for (entry=1; entry < 4; entry++){
    document.getElementById("qinput_checkbox"+entry).setAttribute("opacity", "0.5");
    document.getElementById("qinput_checkbox"+entry).setAttribute("fill", "black");
  }
  if (answerID != 0){
    document.getElementById("qinput_checkbox"+answerID).setAttribute("opacity", "0.8");
    document.getElementById("qinput_checkbox"+answerID).setAttribute("fill", "lime");
    okcontent[3] = true;
  }
  chosen_answer = answerID;
  inputUpdate();
}

var tempTab = []
//déclenchée par clic sur le bouton "Ajouter"; si toutes les conditions de okcontent sont positives, ajoute correctement le contenu de l'interface d'ajout au système de questions (questionTab); 
function validate(){
  if (okcontent[0] == 1){
    counter = 0;
    for (entry=1; entry < 4; entry++){
      if (okcontent[entry] == true){
        counter = counter + 1;
      }
      else{
        break;
      }
    }
    //vérifie si il faut ajouter une ligne secondaire aux réponses
    if (counter == 3){
      tempTab = [document.getElementById("qinput_id").value, 
      document.getElementById("qinput_question").value, 
      chosen_answer, 
      document.getElementById("qinput_answerA1").value, 
      document.getElementById("qinput_answerA2").value, 
      document.getElementById("qinput_answerA3").value];

      if ((document.getElementById("qinput_answerB1").value == "" 
      || document.getElementById("qinput_answerB1").value == "(Ligne 2*)") == true && (document.getElementById("qinput_answerB2").value == "" 
      || document.getElementById("qinput_answerB2").value == "(Ligne 2*)") == true && (document.getElementById("qinput_answerB3").value == ""
      || document.getElementById("qinput_answerB3").value == "(Ligne 2*)") == true){
        alert('push')
        tempTab.push("0");
      }
      else{
        for (entry=1; entry < 4; entry++){
          if (document.getElementById("qinput_answerB"+entry).value == "(Ligne 2*)"){
            document.getElementById("qinput_answerB"+entry).value = "";
          }
        }
        tempTab.push(document.getElementById("qinput_answerB1").value, document.getElementById("qinput_answerB2").value, document.getElementById("qinput_answerB3").value);
      }

      questionTab.push(tempTab);

      //pseudo-réinitialisation de l'interface d'ajout de question
      document.getElementById("qinput_question").value = "Question Ajoutée";
      for (entry=1; entry < 4; entry++){
        document.getElementById("qinput_answerA"+entry).value = "";
        document.getElementById("qinput_answerB"+entry).value = "";
      }
      chosenAnswerManager('0');
    }
  }
}

var noMoreThanOne = false
//intègre les questions par défaut
function normativePusher(){
  if (noMoreThanOne == false){
    questionTab.push([2, "troncature de 1.7", 1, "1", "1.52", "2", 0])
    questionTab.push([3, "obwo", 3, "blah", "bloog", "bl✨h", 0])
    questionTab.push([4, "Le président américain de 2020 sera ", 2, "Bernie", "Andrew", "Donald", "Sanders", "Yang", "Trump"])
    questionTab.push([5, "Nous sommes incapables d'observer un photon.", 3, "non", "explosion", "ouaip", 0])
    questionTab.push([6, "La littérature est...", 1, "un art", "de la philo", "une Science", 0])
    questionTab.push([7, "... n'est pas une propriété d'une particule subatomique", 2, "le Spin", "la Largeur", "la Couleur", 0])
    questionTab.push([8, "Parmis les jeux suivants, lequel n'intègre pas nativement d'entités programmées par les joueurs ?", 2, "VR Chat", "Minecraft", "Garry's Mod", 0])
    questionTab.push([9, "Une vérité absolue concernant le monde physique nécessite...", 1, "l'omniscience", "une réflexion", "une preuve", "(tout savoir)", "philosophique", "expérimentale"])
    questionTab.push([10, "Une théorie qui fait consensus...", 3, "est Toujours", "est Parfois", "n'est Jamais", "prouvée vraie", "prouvée vraie", "prouvée vraie"])

    noMoreThanOne = true
  }
}