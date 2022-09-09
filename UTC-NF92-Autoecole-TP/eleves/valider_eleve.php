<html>

  <head>
    <meta charset="utf-8">
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>
  <body>

    <?php

      // EXTRACTION DES VARIABLES

      date_default_timezone_set('Europe/Paris');
      $date = date("Y-m-d");

      $nom = $_POST["nomEleve"];
      $prenom = $_POST["prenomEleve"];
      $naissance = $_POST["dateEleve"];

      // TESTS DE CONFORMITE (au cas ou le formulaire hidden de ajouter_eleve.php est ignoré)

      $conforme = True;

      if (empty($nom) || empty($prenom) || empty($naissance))
      {
        echo "Erreur : Toutes les valeurs doivent etre remplies. L'élève n'a pas été ajouté.";
        $conforme = False;
      }
      elseif (!is_string($nom) || !is_string($prenom) || !is_string($naissance))
      {
        echo "Erreur : Nom, prenom et la date de naissance doivent etre des chaines de caracteres. L'élève n'a pas été ajouté.";
        $conforme = False;
      }
      elseif (!strtotime($naissance))
      {
        echo "Erreur : La date de naissance doit etre une date valide. L'élève n'a pas été ajouté.";
        $conforme = False;
      }
      elseif (strtotime($naissance) > strtotime($date))
      {
          echo "Erreur : La date de naissance dépasse la date actuelle. L'élève n'a pas été ajouté.";
          $conforme = False;
      }
      elseif ($nom != strip_tags($nom) || $prenom != strip_tags($prenom)) 
      {
        echo "Erreur : Des éléments html ont été utilisés dans les informations de l'élève. L'élève n'a donc pas pu être ajouté.";
        $conforme = False;
      }
      
      if ($conforme) {

        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

        // INSERTION (sans test de confirmite prealable)

        $query = "INSERT INTO eleves (nom, prenom, dateNaiss, dateInscription) VALUES ('$nom', '$prenom', '$naissance', '$date')";
        
        $result = mysqli_query($connect, $query);
        if (!$result) 
        {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans valider_eleve.php section INSERTION<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }
        else 
        {
          echo "<div class='alert'><p>&#9989</p><p>L'élève $prenom $nom né le $naissance a été ajouté</p></div>";
        }

        // DECONNEXION
        
        mysqli_close($connect);
      }
    ?>

  </body>
</html>
