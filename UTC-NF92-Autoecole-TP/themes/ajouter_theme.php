<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
 
  </head>

  <body>
    <?php
      // EXTRACTION DES VARIABLES ""html spread chrwsdff; msqli-real-scope-phfnzdi

      $nom = $_POST["nomTheme"];
      $descriptif = $_POST["descriptifTheme"];

      // TESTS DE CONFORMITE 

      $continue = True;

      if (empty($nom) || empty($descriptif))
      {
        echo "<div class='alert'><p>&#10060</p><p>Toutes les valeurs doivent etre remplies. Le thhème n'a pas été ajouté.</p></div>";
        $continue = False;
      }
      elseif ($nom != strip_tags($nom) || $descriptif != strip_tags($descriptif)) 
      {
        "<div class='alert'><p>&#10060</p><p>Des éléments html ont été détectés dans les informations du thème. e thème n'a pas pu être ajouté.</p></div>";
        $continue = False;
      }
      
      if ($continue) {

        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8');

        // nettoyage des donnees
        $nom = mysqli_real_escape_string($connect, $nom);
        $descriptif = mysqli_real_escape_string($connect, $descriptif);

        // CONFIRMITE DE LA BASE DE DONNEES

        // verifie si un theme avec le meme mon existe, et si il est supprime
        $query = "SELECT supprime FROM themes WHERE nom = '$nom'";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans ajouter_theme.php section CONFORMITE DE LA BASE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
          $continue = false;
        }
        elseif (mysqli_num_rows($result) > 0) // Le theme existe deja
        {
          $supprime = mysqli_fetch_array($result)[0];
          if ($supprime) {
            echo "<div class='content'>";
            echo "<div class='header'><p>Vous avez saisi le nom d'un thème qui a été supprimé. Vous pouvez le réactiver tel qu'il était ou le mettre à jour en remplaçant sa description par celle que vous avez saisi.</p></div>";
            
            echo "<form method='POST' action='valider_theme.php' > <div class='container'>";
            echo "<input type='hidden' value='$nom' name='nomTheme'>";
            echo "<input type='hidden' value='$descriptif' name='descriptifTheme'>";
            echo "<input type='submit' name='action' value='Reactiver'>";
            echo "<input type='submit' name='action' value='Mettre à Jour'>"; 
            echo "<a href='ajout_theme.html'><p>Annuler et revenir en arrière</p></a>";

            echo "</div></form></div>";
          }
          else {
            echo "<div class='alert'><p>&#10060</p><p>Aucun changement n'a été effectué car le thème existe déjà et est actif.</p></div>";
          }
          $continue = false;
        }
      }

      if ($continue) {
        // AJOUTER LE THEME

        $query = "INSERT INTO themes (nom, descriptif) VALUES ('$nom', '$descriptif')";

        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans ajouter_theme.php section AJOUTER<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }
        else {
        echo "<div class='alert'><p>&#9989</p><p>Le thème $nom a été ajouté</p></div>";
        }
        mysqli_close($connect);
      }

    ?>
  </body>

</html>
