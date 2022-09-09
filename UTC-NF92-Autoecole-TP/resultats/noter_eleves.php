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

      $idseance = $_POST["idseance"];
      // les notes des eleves seront extraites et verifiees plus bas (RECUPERATION NOTES)

      // TESTS DE CONFORMITE 

      $continue = True;

      if (!is_numeric($idseance))
      {
        echo "<div class='alert'><p>&#10060</p><p>Valeurs Anormales</p></div>";
        $continue = False;
      }

      if ($continue) {

        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

        // OBTENTION LISTE ELEVES

        $query = "SELECT I.ideleve, I.note FROM inscription AS I WHERE idseance = '$idseance'";
        $result = mysqli_query($connect, $query);
        if (!$result) {
          echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans noter_eleves.php section OBTENTION<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
        }

        // RECUPERATION NOTES, INSERTION DB

        $confirm = "<br>"; // message de confirmation

        while ($deleve = mysqli_fetch_array($result, MYSQLI_NUM)) {

          // DONNEES ELEVES POUR CONFIRMATION, DEBUG

          $query = "SELECT prenom, nom FROM eleves WHERE ideleve = '$deleve[0]'";
          $result_ = mysqli_query($connect, $query);
          if (!$result_) {
            echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans noter_eleves.php section DONNEES ELEVES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
          }
          $dverif = mysqli_fetch_array($result_);

          // TEST DE CONFORMITE NOTE

          $note = $_POST["$deleve[0]"];
          if ($note) { // si il n'y a pas de note, ne rien changer
            if (!is_numeric($note)) {
              echo "<div class='alert'><p>&#10060</p><p>La note saisie pour $dverif[0] $dverif[1] n'est pas un nombre.<br>La note n'a pas été changée pour cet élève.</p></div>";
            }
            elseif (($note < 0 && $note != -1) || $note > 20) {
              echo "<div class='alert'><p>&#10060</p><p>La note saisie pour $dverif[0] $dverif[1] dépasse l'intervalle d'une note (entre 0 et 40).<br>La note n'a pas été changée pour cet élève.</p></div>";
            }
            elseif ($note != $deleve[1]) { // ne met a jour la note que si elle n'est pas identique a la note actuelle
              
              // MISE A JOUR NOTE

              $query = "UPDATE inscription SET note = '$note' WHERE ideleve = '$deleve[0]' AND idseance = '$idseance'";
              $result__ = mysqli_query($connect, $query);
              if (!$result__) {
                echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans noter_eleves.php section MISE A JOUR<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
              }
              else {
                // confirmation 
                $confirm .= "<br>$dverif[0] $dverif[1]";
              }
            }
          }
        }
        if ($confirm == "<br>") {
          echo "<div class='alert'><p>&#9989</p><p>Aucune note n'a été modifiée.</p></div>";
        }
        else {
          echo "<div class='alert'><p>&#9989</p><p><br>Les notes des élèves suivants ont été modifiées :".$confirm."</br></p></div>";
        }

        // DECONNEXION
        
        mysqli_close($connect);
      }
    ?>

  </body>

</html>
