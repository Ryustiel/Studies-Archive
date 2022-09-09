<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>

  <body>
    <?php
      // EXTRACTION DES VARIABLES

      date_default_timezone_set('Europe/Paris');
      $date = date("Y-m-d");

      $idthemes = $_POST["idthemes"]; // array

      if (empty($_POST["deleteSeances"])) {
        $deleteSeances = false;
      }
      else {
        $deleteSeances = true;
      }

      // TESTS DE CONFORMITE 

      $continue = True;

      if (is_iterable($idthemes)) {
        foreach($idthemes as $id) {
          if (!is_numeric($id))
          {
            echo "<div class='alert'><p>&#10060</p><p>Valeurs Anormales</p></div>";
            $continue = False;
            break;
          }
        }
      }
      else {
        echo "<div class='alert'><p>&#10060</p><p>La liste des themes n'est pas iterable.</p></div>";
        $continue = False;
      }

      // CONFORMITE DE LA BASE DE DONNEES

      if ($continue) {

        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8');

      }

      if ($continue) {

        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

        // DESACTIVE LES THEMES

        if (is_iterable($idthemes)) {
          $count = 0;
          foreach ($idthemes as $idtheme) {

            // CONFIRMITE DE LA BASE DE DONNEES

            // recherche si les themes a supprimer existent bien dans la base de donnees
            $query = "SELECT idtheme FROM themes WHERE idtheme = '$idtheme'";
            
            $result = mysqli_query($connect, $query);
            if (!$result)
            {
              echo "<div class='alert'><p>&#10060</p><p>Le thème n'a pas été supprimé.<br>Erreur SQL dans supprimer_theme.php section CONFORMITE DE LA BASE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
              $continue = False;
            }
            elseif (mysqli_num_rows($result) == 0) // le theme n'existe pas
            {
              echo "<div class='alert'><p>&#10060</p><p>Le thème n'existe pas</p></div>";
              $continue = False;
            }
          }

          if ($continue) {
            
            $query = "UPDATE themes AS T SET T.supprime = 1 WHERE T.idtheme = $idtheme";
            $result = mysqli_query($connect, $query);    
            if (!$result) {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans supprimer_theme.php section DESACTIVER<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            }  
            
            $query = "SELECT nom FROM themes as T WHERE T.idtheme = $idtheme";
            $result_ = mysqli_query($connect, $query);
            if (!$result_) {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans supprimer_theme.php section DESACTIVER THEMES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            }
            $themeName = mysqli_fetch_array($result_, MYSQLI_NUM);
            $count += 1;
          }
          echo "<div class='alert'><p>&#9989</p><p>$count thèmes ont été supprimés</p></div>";

          if ($deleteSeances) 
          {
            // supprime egalement les seances associees
            
            $count = 0;
            foreach ($idthemes as $idtheme) {

              // RECUPERE LES SEANCES A SUPPRIMER 

              $query = "SELECT idseance FROM seances WHERE idtheme = $idtheme AND dateSeance >= '$date'";
              $result = mysqli_query($connect, $query);
              if (!$result_)
                {
                  echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans supprimer_theme.php section SELECTIONNE SEANCES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
                }
              else {
                while ($dseance = mysqli_fetch_array($result))
                {
                  // DESINSCRIT les eleves

                  $query = "DELETE FROM inscription WHERE idseance = '$dseance[0]'";
                  $result_ = mysqli_query($connect, $query);
                  if (!$result_)
                  {
                    echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans supprimer_theme.php section DESINSCRIT ELEVES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
                  }
                  // SUPPRIME la seance de la base de donnees

                  $query = "DELETE FROM seances WHERE idseance = '$dseance[0]'";
                  $result_ = mysqli_query($connect, $query);
                  if (!$result_)
                  {
                    echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans supprimer_theme.php section SUPPRIME SEANCES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
                  }
                  else {$count += 1;}
                }
              }
            }
            echo "<div class='alert'><p>&#9989</p><p>$count séances ont été supprimées</p></div>";
          }
        }
        else {
          echo "<div class='alert'><p>&#10060</p><p>la liste des thèmes n'est pas itérable.</p></div>";
        }

        // DECONNEXION
        
        mysqli_close($connect);
      }
    ?>
  </body>

</html>
