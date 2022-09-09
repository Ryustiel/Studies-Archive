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

        // TESTS DE CONFORMITE 

        $continue = True;

        if (empty($nom) || empty($prenom) || empty($naissance))
        {
          echo "<div class='alert'><p>&#10060</p><p>Toutes les valeurs doivent etre remplies. L'élève n'a pas été ajouté.</p></div>";
          $continue = False;
        }
        elseif (!strtotime($naissance))
        {
          echo "<div class='alert'><p>&#10060</p><p>La date de naissance doit etre une date valide. L'élève n'a pas été ajouté.</p></div>";
          $continue = False;
        }
        elseif (strtotime($naissance) > strtotime($date))
        {
          echo "<div class='alert'><p>&#10060</p><p>La date de naissance dépasse la date actuelle. L'élève n'a pas été ajouté.</p></div>";
            $continue = False;
        }
        elseif ($nom != strip_tags($nom) || $prenom != strip_tags($prenom)) 
        {
          echo "<div class='alert'><p>&#10060</p><p>Des éléments html ont été détectés dans les informations de l'élève. L'élève n'a donc pas pu être ajouté.</p></div>";
          $continue = False;
        }

        $nom = htmlspecialchars($nom);
        $prenom = htmlspecialchars($prenom);
        
        if ($continue) 
        {

          // CONNEXION

          $dbhost = 'tuxa.sme.utc';
          $dbuser = 'nf92p065';
          $dbpass = 'uhJECSt3';
          $dbname = 'nf92p065';

          $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
          mysqli_set_charset($connect, 'utf8');

          // nettoyage des donnees
          $nom = mysqli_real_escape_string($connect, $nom);
          $prenom = mysqli_real_escape_string($connect, $prenom);

          // CONFIRMITE DE LA BASE DE DONNEES

          $query = "SELECT ideleve FROM eleves AS E WHERE E.nom = '$nom' AND E.prenom = '$prenom'";
          
          $result = mysqli_query($connect, $query);
          if (!$result) {
            echo "<div class='alert'><p>&#10060</p><p>L'élève n'a pas été ajouté.<br>Erreur SQL dans ajouter_eleve.php section CONFORMITE DE LA BASE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            $continue = False;
          }
          elseif (mysqli_num_rows($result) > 0) // au moins un eleve existe deja avec ce couple nom, prenom
          {
            echo "<div class='content'>";
            echo "<div class='header'><p>L'élève $prenom $nom né le $naissance existe déjà dans la base de données. Voulez-vous l'ajouter quand même ?</p></div>";

            echo "<div class='content'><form method='POST' action='valider_eleve.php' >";
            echo "<input type='hidden' value='$nom' name='nomEleve'>";
            echo "<input type='hidden' value='$prenom' name='prenomEleve'>";
            echo "<input type='hidden' value='$naissance' name='dateEleve'>";
            echo "<input type='submit' value='Oui'>"; 
            echo "<a href='ajout_eleve.html'><p>Non, revenir en arrière</p></a>";

            echo "</form></div></div>";
            $continue = False;
          }
        }

        if ($continue) 
        {

          // INSERTION

          $query = "INSERT INTO eleves (nom, prenom, dateNaiss, dateInscription) VALUES ('$nom', '$prenom', '$naissance', '$date')";

          $result = mysqli_query($connect, $query);
          if (!$result) 
          {
            echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans ajouter_eleve.php section INSERTION<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
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
